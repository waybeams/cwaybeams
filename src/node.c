#include "node.h"
#include "fnv.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

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
 * -1 if the NodeAttr is not found.
 *
 *  NOTE(lbayes): When it becomes clear that this is a performance problem,
 *  try adding a lookup table to Node where attr Name enum values can
 *  return the index where the attr is found.
 *
 *  I'm deferring this work for the moment, as this does the job and also
 *  works with duplicate attribute entries without too much extra complexity.
 */
static int get_attr_index_by_type(Node *node, int type) {
  Attr *attr;
  for (int i = 0; i < node->attr_count; i++) {
    attr = node->attrs[i];
    if (attr->type == type) {
      return i;
    }
  }
  return -1;
}

/**
 * Free all malloc'd data from the provided attribute through any references it
 * may contain, including child Nodes.
 */
void free_attr(Attr *attr) {
  if (attr->type == NodeAttrChildren) {
    struct Node **kids = get_nodes_attr(attr);
    int count = attr->data_size / POINTER_SIZE;
    for (int i = 0; i < count; i++) {
      free_node(kids[i]);
    }
  }

  // Function pointers are allocated outside this library.
  if (attr->type < NodeAttrFunction) {
    free(attr->data);
  }

  free(attr);
}

/**
 * Recursively free all malloc'd data from the provided
 * element to it's leaves.
 */
void free_node(Node *node) {
  for (int i = 0; i < node->attr_count; i++) {
    Attr *attr = node->attrs[i];
    free_attr(attr);
  }
  free(node->attrs);
  free(node);
}

/**
 * Create and returne a new, empty attribute struct.
 *
 * These entities must be sent to 'free_attr' at some point in the future.
 */
Attr *new_attr(void) {
  Attr *attr = malloc(sizeof(struct Attr));
  if (attr == NULL) {
    return NULL;
  }
  attr->type = 0;
  attr->data_size = 0;
  return attr;
}

/**
 * Create a new Attr with the provided char value.
 */
Attr *new_char_attr(NodeAttr type, char *value) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->type = type;
  attr->data_size = strlen(value) + 1;
  attr->data = (unsigned char *)malloc(attr->data_size);
  memcpy(attr->data, value, attr->data_size);
  return attr;
}

/**
 * Get the data from a Char Attr as (char *).
 */
char *get_char_attr_data(Attr *attr) {
  return (char *)get_attr_data(attr);
}

inline unsigned char *get_attr_data(Attr *attr) {
  return attr->data;
}

/**
 * Create a new Attr with the provided type and unsigned int data.
 */
Attr *new_uint_attr(NodeAttr type, unsigned int value) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->type = type;
  attr->data_size = sizeof(unsigned int);
  attr->data = malloc(attr->data_size);
  memcpy(attr->data, &value, attr->data_size);
  return attr;
}

/**
 * Get the provided Attribute data as an unsigned integer.
 */
unsigned int get_uint_attr_data(Attr *attr) {
  return *(unsigned int *)get_attr_data(attr);
}

/**
 * Create a new attribute with an unsigned char * pointer value and
 * the provided type.
 */
Attr *new_ptr_attr(NodeAttr type, unsigned char *value) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->type = type;
  attr->data_size = POINTER_SIZE;
  attr->data = value;
  return attr;
}

/**
 * Get the provided Node children collection.
 */
struct Node **get_children(Node *node) {
  int index = get_attr_index_by_type(node, (NodeAttr)NodeAttrChildren);
  if (index > -1) {
    return get_nodes_attr(node->attrs[index]);
  }

  return NULL;
}

char *get_char_attr_from_node(Node *node, NodeAttr type, char *default_value) {
  int index = get_attr_index_by_type(node, type);
  if (index > -1) {
    return get_char_attr_data(node->attrs[index]);
  }

  return default_value;
}

unsigned int get_uint_attr_from_node(Node *node, NodeAttr type,
    unsigned int default_value) {
  int index = get_attr_index_by_type(node, type);
  if (index > -1) {
    return get_uint_attr_data(node->attrs[index]);
  }

  return default_value;
}

unsigned char *get_raw_attr_from_node(Node *node, NodeAttr type) {
  int index = get_attr_index_by_type(node, type);
  if (index > -1) {
    Attr *attr = node->attrs[index];
    return get_attr_data(attr);
  }

  return NULL;
}

/**
 * Create a children Attr.
 */
Attr *new_children(unsigned int count, ...) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }

  attr->type = NodeAttrChildren;
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
struct Node **get_nodes_attr(Attr *attr) {
  return (struct Node **)get_attr_data(attr);
}

static NodeHash hash_char_attr(Attr *attr) {
  NodeHash *hash = malloc(sizeof(NodeHash));
  return *hash;
}

static NodeHash *hash_attr(Attr *attr) {
  return NULL;
}

static NodeHash hash_node(Node *node) {
  NodeHash hash;
  // NodeHash hash = (NodeHash)fnv_32a_buf(node->child_count, 1, 0);
  // Attr *attr = get_name(node);
  // for (int i = 0; i < node->attr_count; i++) {
    // attr = node->attrs[i];
    // hash += hash_attr(attr);
  // }

  return hash;
}

/**
 * Create a new Node with the provided attributes.
 */
Node *new_node(NodeType type, unsigned int attr_count, ...) {
  struct Attr **attrs = malloc(attr_count * POINTER_SIZE);
  if (attrs == NULL) {
    return NULL;
  }
  Node *node = malloc(sizeof(struct Node));
  node->id = getNextId();
  node->type = type;
  node->parent_id = 0;
  node->child_count = 0;

  // Process Attrs
  va_list vargs;
  va_start(vargs, attr_count);
  for (int i = 0; i < attr_count; i++) {
    struct Attr *attr = va_arg(vargs, struct Attr *);
    if (attr->type == NodeAttrChildren) {
        node->child_count += (attr->data_size / POINTER_SIZE);
        struct Node **kids = get_nodes_attr(attr);
        for (int k = 0; k < node->child_count; k++) {
            kids[k]->parent_id = node->id;
        }
    }
    attrs[i] = attr;
  }
  va_end(vargs);

  node->attr_count = attr_count;
  node->attrs = attrs;
  node->hash = hash_node(node);

  return node;
}

void print_element_indented(Node *node, char *indent) {
  printf("------------------------\n");
  printf("%snode.id: %ld\n", indent, node->id);
  printf("%snode.parent_id: %ld\n", indent, node->parent_id);
  // printf("%snode.type: %s\n", indent, get_type(node));
  struct Node **kids = get_children(node);
  if (kids != NULL) {
    char *nextIndent = malloc(strlen(indent) + 2);
    nextIndent = strcpy(nextIndent, indent);
    nextIndent = strcat(nextIndent, "\t");
    for (int i = 0; i < node->child_count; i++) {
      print_element_indented(kids[i], nextIndent);
    }
    free(nextIndent);
  }
}

/**
 * Print the provided node and attributes.
 */
void print_node(Node *node) {
  char *empty = malloc(1);
  print_element_indented(node, "");
  free(empty);
}

/**
 * Call any handlers found for the provided gesture type.
 */
void emit_event(Node *node, char *gesture_name) {
  int index = get_attr_index_by_type(node, NodeAttrFunction);
  if (index > -1) {
    Attr *attr = node->attrs[index];
    GestureHandler gestureHandler = (GestureHandler)get_attr_data(attr);
    gestureHandler();
  }
}

/**
 * Return true if the provided Node does not have an assigned parent_id.
 */
bool is_root(Node *node) {
  return node->parent_id == 0;
}

