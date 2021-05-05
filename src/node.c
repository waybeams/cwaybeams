#include "node.h"
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

static void node_to_str_indented(char *dest, Node *node, char *indent);

/**
 * Get the next incremental identifier.
 */
static NodeId getNextId() {
  return lastId++;
}

/**
 * Get the index of the provided attribute for the provided Node, or return
 * -1 if the AttrType is not found.
 *
 *  NOTE(lbayes): When it becomes clear that this is a performance problem,
 *  try adding a lookup table to Node where attr Name enum values can
 *  return the index where the attr is found.
 *
 *  I'm deferring this work for the moment, as this does the job and also
 *  works with duplicate attribute entries without too much extra complexity.
 */
static int get_attr_index_by_key(Node *node, AttrKey key) {
  Attr *attr;
  for (int i = 0; i < node->attr_count; i++) {
    attr = node->attrs[i];
    if (attr->key == key) {
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
  if (attr->type == NodeAttrTypesChildren) {
    struct Node **kids = get_children_attr_data(attr);
    int count = attr->data_size / POINTER_SIZE;
    for (int i = 0; i < count; i++) {
      free_node(kids[i]);
    }
  }

  // Function pointers are allocated outside this library.
  if (attr->type != NodeAttrTypesExtPtr) {
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
  attr->type = NodeAttrTypeNone;
  attr->key = NodeAttrKeysNone;
  attr->data_size = 0;
  return attr;
}

/**
 * Create a new Attr with the provided char value.
 */
Attr *new_char_attr(AttrKey key, char *value) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  if (value == NULL) {
    value = "";
  }
  attr->key = key;
  attr->type = NodeAttrTypesChars;
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
Attr *new_uint_attr(AttrKey key, unsigned int value) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->key = key;
  attr->type = NodeAttrTypesUint;
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
Attr *new_ptr_attr(AttrKey key, unsigned char *value) {
  Attr *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->key = key;
  attr->type = NodeAttrTypesPtr;
  attr->data_size = POINTER_SIZE;
  attr->data = value;
  return attr;
}

/**
 * Just like a pointer attribute, but will not be freed
 * by our calls to free_attr().
 */
Attr *new_ext_ptr_attr(AttrKey key, unsigned char *value) {
  Attr *attr = new_ptr_attr(key, value);
  if (attr == NULL) {
    return NULL;
  }
  // Replace the type to avoid automatic free calls.
  attr->type = NodeAttrTypesExtPtr;
  return attr;
}

/**
 * Get the provided Node children collection.
 */
struct Node **get_children(Node *node) {
  int index = get_attr_index_by_key(node, NodeAttrKeysChildren);
  if (index > -1) {
    return get_children_attr_data(node->attrs[index]);
  }

  return NULL;
}

char *get_char_attr_from_node(Node *node, AttrKey key, char *default_value) {
  int index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_char_attr_data(node->attrs[index]);
  }

  return default_value;
}

unsigned int get_uint_attr_from_node(Node *node, AttrKey key,
    unsigned int default_value) {
  int index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_uint_attr_data(node->attrs[index]);
  }

  return default_value;
}

unsigned char *get_raw_attr_from_node(Node *node, AttrKey key) {
  int index = get_attr_index_by_key(node, key);
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

  attr->type = NodeAttrTypesChildren;
  attr->key = NodeAttrKeysChildren;
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
struct Node **get_children_attr_data(Attr *attr) {
  return (struct Node **)get_attr_data(attr);
}

static NodeHash hash_node(Node *node) {
  char node_str[1024] = {0};
  node_to_str(node_str, node);
  return fast_hash(node_str, strlen(node_str));
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
    if (attr->key == NodeAttrKeysChildren) {
        node->child_count += (attr->data_size / POINTER_SIZE);
        struct Node **kids = get_children_attr_data(attr);
        for (int k = 0; k < node->child_count; k++) {
            kids[k]->parent_id = node->id;
        }
    }
    attrs[i] = attr;
  }
  va_end(vargs);

  node->attr_count = attr_count;
  node->attrs = attrs;
  // node->hash = hash_node(node);
  return node;
}

/**
 * Call any handlers found for the provided gesture type.
 */
void emit_event(Node *node, AttrKey key, char *gesture_name) {
  int index = get_attr_index_by_key(node, key);
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

static void attr_chars_to_str(char *dest, Attr *attr, char *indent) {
  sprintf(dest, "%s attr_%d.%s=%s", dest, attr->key, NODE_ATTR_CHARS, attr->data);
}

static void attr_to_str(char *dest, Attr *attr, char *indent) {
  sprintf(dest, "%s attr_%d.type=%d", dest, attr->key, attr->type);

  switch (attr->type) {
    case NodeAttrTypesChars:
      attr_chars_to_str(dest, attr, indent);
      break;
  }
}

static void node_children_to_str(char *dest, Node *node, char *indent) {
  struct Node **kids = get_children(node);
  if (kids != NULL) {
    sprintf(indent, "%s\t", indent);
    for (int i = 0; i < node->child_count; i++) {
      node_to_str_indented(dest, kids[i], indent);
    }
  }
}

static void node_to_str_indented(char *dest, Node *node, char *indent) {
  sprintf(dest, "%s\n%snode.type=%d", dest, indent, node->type);

  for (int i = 0; i < node->attr_count; i++) {
    attr_to_str(dest, node->attrs[i], indent);
  }

  node_children_to_str(dest, node, indent);
}

void node_to_str(char *dest, Node *node) {
  char indent[128] = {0};
  node_to_str_indented(dest, node, indent);
}

/*
static size_t node_to_char_len(Node *node) {
  size_t len = 0;
  return snprintf(NULL, len, "%d", node->type);
}
*/

/**
 * Print the provided node and attributes.
 */
void print_node(Node *node) {
  char dest[512] = {0};
  node_to_str(dest, node);
  printf("%s\n", dest);
}
