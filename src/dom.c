#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Global id for all instantiated Nodes.
 */
static NodeId lastId = 1;

/**
 * Simple pointer, used to determine pointer size.
 */
static int *ptr;

/**
 * Size of a pointer on this compilation target.
 */
static uint8_t POINTER_SIZE = sizeof(ptr);

/**
 * Get the next incremental identifier.
 */
static NodeId getNextId() {
  return lastId++;
}

/**
 * Get the index of the provided attribute for the provided Node, or return
 * -1 if the AttrName is not found.
 *
 *  NOTE(lbayes): When it becomes clear that this is a performance problem,
 *  try adding a lookup table to Node where attr Name enum values can
 *  return the index where the attr is found.
 *
 *  I'm deferring this work for the moment, as this does the job and also
 *  works with duplicate attribute entries without too much extra complexity.
 */
static int getAttrIndexByName(Node *node, AttrName name) {
  for (int i = 0; i < node->attr_count; i++) {
    if (node->attrs[i]->name == name) {
      return i;
    }
  }
  return -1;
}

/**
 * Free all malloc'd data from the provided attribute through any references it
 * may contain, including child Nodes.
 */
void freeAttr(Attr *attr) {
  if (attr->name == ChildrenAttr) {
    struct Node **kids = getElementsAttr(attr);
    int count = attr->data_size / POINTER_SIZE;
    for (int i = 0; i < count; i++) {
      freeNode(kids[i]);
    }
  }

  if (attr->name != GestureHandlerAttr &&
      attr->name != HandlerAttr) {
    free(attr->data);
  }

  free(attr);
}

/**
 * Recursively free all malloc'd data from the provided
 * element to it's leaves.
 */
void freeNode(Node *node) {
  for (int i = 0; i < node->attr_count; i++) {
    Attr *attr = node->attrs[i];
    freeAttr(attr);
  }
  free(node->attrs);
  free(node);
}

/**
 * Create and returne a new, empty attribute struct.
 *
 * These entities must be sent to 'freeAttr' at some point in the future.
 */
Attr *newAttr(void) {
  Attr *attr = malloc(sizeof(struct Attr));
  if (attr == NULL) {
    return NULL;
  }
  attr->data_size = 0;
  return attr;
}

/**
 * Create a new Attr with the provided char value.
 */
Attr *newCharAttr(AttrName name, char *value) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = name;
  attr->data_size = strlen(value) + 1;
  attr->data = (unsigned char *)malloc(attr->data_size);
  memcpy(attr->data, value, attr->data_size);
  return attr;
}

/**
 * Get the data from a Char Attr as (char *).
 */
char *getCharAttr(Attr *attr) {
  return (char *)attr->data;
}

/**
 * Create a new Attr with the provided name and unsigned int data.
 */
Attr *newUintAttr(AttrName name, unsigned int value) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = name;
  attr->data_size = sizeof(unsigned int);
  attr->data = malloc(attr->data_size);
  memcpy(attr->data, &value, attr->data_size);
  return attr;
}

/**
 * Get the provided Attribute data as an unsigned integer.
 */
unsigned int getUintAttr(Attr *attr) {
  return *(unsigned int *)attr->data;
}

/**
 * Create a new Gesture handler Attr.
 */
Attr *newHandlerAttr(AttrName name, GestureHandler handler) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = name;
  attr->data_size = POINTER_SIZE;
  attr->data = (unsigned char *)handler;
  return attr;
}

Attr *newSignalHandlerAttr(AttrName name, SignalHandler handler) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = name;
  attr->data_size = POINTER_SIZE;
  attr->data = (unsigned char *)handler;
  return attr;
}

/**
 * Get the provided Node children collection.
 */
struct Node **getChildren(Node *node) {
  int index = getAttrIndexByName(node, ChildrenAttr);
  if (index > -1) {
    return getElementsAttr(node->attrs[index]);
  }

  return NULL;
}

char *getCharAttrFromNode(Node *node, AttrName name, char *defaultValue) {
  int index = getAttrIndexByName(node, name);
  if (index > -1) {
    return getCharAttr(node->attrs[index]);
  }

  return defaultValue;
}

unsigned int getUintAttrFromNode(Node *node, AttrName name,
    unsigned int defaultValue) {
  int index = getAttrIndexByName(node, name);
  if (index > -1) {
    return getUintAttr(node->attrs[index]);
  }

  return defaultValue;
}

unsigned char *getRawAttrFromNode(Node *node, AttrName name) {
  int index = getAttrIndexByName(node, name);
  if (index > -1) {
    Attr *attr = node->attrs[index];
    return attr->data;
  }

  return NULL;
}

/**
 * Create a children Attr.
 */
Attr *newChildren(unsigned int count, ...) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }

  attr->name = ChildrenAttr;
  attr->data_size = count * POINTER_SIZE;

  struct Node *kids[attr->data_size];
  if (kids == NULL) {
    return NULL;
  }

  va_list vargs;
  va_start(vargs, count);
  for (int i = 0; i < count; i++) {
    struct Node *kid = va_arg(vargs, struct Node *);
    kids[i] = kid;
  }
  va_end(vargs);

  attr->data = (unsigned char *)malloc(attr->data_size);
  if (attr->data == NULL) {
    return NULL;
  }
  memcpy(attr->data, kids, attr->data_size);
  return attr;
}

/**
 * Get an array of Node pointers as Children data from the provided Attr.
 */
struct Node **getElementsAttr(Attr *attr) {
  return (struct Node **)attr->data;
}

/**
 * Create a new Node with the provided attributes.
 */
Node *newNode(NodeType type, unsigned int attr_count, ...) {
  struct Attr **attrs = malloc(attr_count * POINTER_SIZE);
  if (attrs == NULL) {
    return NULL;
  }
  Node *node = malloc(sizeof(struct Node));
  node->id = getNextId();
  node->parent_id = 0;
  node->type = type;
  node->child_count = 0;

  // Process Attrs
  va_list vargs;
  va_start(vargs, attr_count);
  for (int i = 0; i < attr_count; i++) {
    struct Attr *attr = va_arg(vargs, struct Attr *);
    if (attr->name == ChildrenAttr) {
        node->child_count += (attr->data_size / POINTER_SIZE);
        struct Node **kids = getElementsAttr(attr);
        for (int k = 0; k < node->child_count; k++) {
            kids[k]->parent_id = node->id;
        }
    }
    attrs[i] = attr;
  }
  va_end(vargs);

  node->attr_count = attr_count;
  node->attrs = attrs;

  return node;
}

/**
 * Print each char code in the provided string.
 */
void printChars(char *chars) {
  int i = 0;
  while (chars[i++] != '\0') {
    printf("Char: %d %c\n", chars[i], chars[i]);
  }
}

void printElementIndented(Node *node, char *indent) {
  printf("------------------------\n");
  printf("%snode.id: %ld\n", indent, node->id);
  printf("%snode.parent_id: %ld\n", indent, node->parent_id);
  printf("%snode.name: %s\n", indent, getName(node));
  struct Node **kids = getChildren(node);
  if (kids != NULL) {
    char *nextIndent = malloc(strlen(indent) + 2);
    nextIndent = strcpy(nextIndent, indent);
    nextIndent = strcat(nextIndent, "\t");
    for (int i = 0; i < node->child_count; i++) {
      printElementIndented(kids[i], nextIndent);
    }
    free(nextIndent);
  }
}

/**
 * Print the provided node and attributes.
 */
void printNode(Node *node) {
  char *empty = malloc(1);
  printElementIndented(node, "");
  free(empty);
}

/**
 * Call any handlers found for the provided gesture name.
 */
void emitEvent(Node *node, char *gestureName) {
  int index = getAttrIndexByName(node, GestureHandlerAttr);
  if (index > -1) {
    Attr *attr = node->attrs[index];
    GestureHandler gestureHandler = (GestureHandler)attr->data;
    gestureHandler();
  }
}

/**
 * Return true if the provided Node does not have an assigned parent_id.
 */
bool isRoot(Node *node) {
  return node->parent_id == 0;
}

