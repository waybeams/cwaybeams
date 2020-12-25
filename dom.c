#include "dom.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NAME "default-name"

/**
 * Global id for all instantiated Elements.
 */
static ElementId lastId = 1;

/**
 * Simple pointer, used to determine pointer size.
 */
static int *ptr;

/**
 * Size of a pointer on this compilation target.
 */
static uint8_t POINTER_SIZE = sizeof(ptr);

/**
 * Free all malloc'd data from the provided attribute through any references it
 * may contain, including child Elements.
 */
void freeAttr(Attr *attr) {
  if (attr->name == Children) {
    struct Element **kids = childrenAttrData(attr);
    int count = attr->dataSize / POINTER_SIZE;
    for (int i = 0; i < count; i++) {
      freeElement(kids[i]);
    }
  }
  free(attr->data);
  free(attr);
}

/**
 * Recursively free all malloc'd data from the provided
 * element to it's leaves.
 */
void freeElement(Element *elem) {
  for (int i = 0; i < elem->attrCount; i++) {
    Attr *attr = elem->attrs[i];
    freeAttr(attr);
  }
  free(elem->attrs);
  free(elem);
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
  attr->dataSize = 0;
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
  attr->dataSize = strlen(value) + 1;
  attr->data = (unsigned char *)malloc(attr->dataSize);
  memcpy(attr->data, value, attr->dataSize);
  return attr;
}

/**
 * Get the data from a Char Attr as (char *).
 */
char *charAttrData(Attr *attr) {
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
  attr->dataSize = sizeof(unsigned int);
  attr->data = (unsigned char *)malloc(attr->dataSize);
  memcpy(attr->data, &value, attr->dataSize);
  return attr;
}

/**
 * Get the provided Attribute data as an unsigned integer.
 */
unsigned int uintAttrData(Attr *attr) {
  return (unsigned int)*attr->data;
}

/**
 * Create a children Attr.
 */
Attr *newChildren(unsigned int count, ...) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = Children;
  attr->dataSize = count * POINTER_SIZE;

  struct Element *kids[attr->dataSize];
  if (kids == NULL) {
    return NULL;
  }

  va_list vargs;
  va_start(vargs, count);
  for (int i = 0; i < count; i++) {
    struct Element *kid = va_arg(vargs, struct Element *);
    kids[i] = kid;
  }
  va_end(vargs);

  attr->data = (unsigned char *)malloc(attr->dataSize);
  if (attr->data == NULL) {
    return NULL;
  }
  memcpy(attr->data, kids, attr->dataSize);
  return attr;
}

/**
 * Get an array of Element pointers as Children data from the provided Attr.
 */
struct Element **childrenAttrData(Attr *attr) {
  return (struct Element **)attr->data;
}

/**
 * Concrete Attr names bound to concrete types.
 */

/**
 * Create and return a name attribute.
 */
Attr *name(char *value) {
  return newCharAttr(Name, value);
}

/**
 * Create and return a width attribute.
 */
Attr *width(unsigned int value) {
  return newUintAttr(Width, value);
}

/**
 * Create and return a height attribute.
 */
Attr *height(unsigned int value) {
  return newUintAttr(Height, value);
}

/**
 * Create a new Element with the provided attributes.
 */
Element *newElement(unsigned int attrCount, ...) {
  struct Attr **attrs = malloc(attrCount * POINTER_SIZE);
  if (attrs == NULL) {
    return NULL;
  }
  Element *elem = malloc(sizeof(struct Element));
  elem->id = lastId++;
  elem->parentId = 0;

  // Process Attrs
  va_list vargs;
  va_start(vargs, attrCount);
  for (int i = 0; i < attrCount; i++) {
    struct Attr *attr = va_arg(vargs, struct Attr *);
    if (attr->name == Children) {
      elem->childCount += (attr->dataSize / POINTER_SIZE);
    }
    attrs[i] = attr;
  }
  va_end(vargs);

  elem->attrCount = attrCount;
  elem->attrs = attrs;

  return elem;
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

void printElementIndented(Element *elem, char *indent) {
  printf("------------------------\n");
  printf("%selem.id: %d\n", indent, elem->id);
  printf("%selem.parentId: %d\n", indent, elem->parentId);
  printf("%selem.name: %s\n", indent, elementName(elem));
  struct Element **kids = elementChildren(elem);
  if (kids != NULL) {
    char *nextIndent = malloc(strlen(indent) + 2);
    nextIndent = strcpy(nextIndent, indent);
    nextIndent = strcat(nextIndent, "\t");
    for (int i = 0; i < elem->childCount; i++) {
      printElementIndented(kids[i], nextIndent);
    }
    free(nextIndent);
  }
}

/**
 * Print the provided element and attributes.
 */
void printElement(Element *elem) {
  char *empty = malloc(1);
  printElementIndented(elem, "");
  free(empty);
}

/**
 * Get the provided Element name attribute, or DEFAULT_NAME if one was not
 * provided.
 */
char *elementName(Element *elem) {
  for (int i = 0; i < elem->attrCount; i++) {
    if (elem->attrs[i]->name == Name) {
      return charAttrData(elem->attrs[i]);
    }
  }

  return DEFAULT_NAME;
}

/**
 * Get the provided Element children collection.
 */
struct Element **elementChildren(Element *elem) {
  for (int i = 0; i < elem->attrCount; i++) {
    if (elem->attrs[i]->name == Children) {
      return childrenAttrData(elem->attrs[i]);
    }
  }

  return NULL;
}

