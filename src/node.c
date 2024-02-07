#include "node.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Global id for all instantiated Nodes.
 */
static node_id_t lastId = 1;

/**
 * Size of a pointer on this compilation target.
 */
static u8_t POINTER_SIZE = sizeof(void *);

// static void node_to_str_indented(char *dest, node_t *node, char *indent);

/**
 * Get the next incremental identifier.
 */
static node_id_t getNextId() {
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
static s32_t get_attr_index_by_key(node_t *node, attr_key_t key) {
  attr_t *attr;
  for (u32_t i = 0; i < node->attr_count; i++) {
    attr = node->attrs[i];
    if (attr->key == key) {
      return i;
    }
  }
  return -1;
}

static int attr_should_be_freed(attr_t *attr) {
  return (attr->type == NodeAttrTypesChars &&
          attr->data_size > 0) // is *char & len > 0
       || attr->type != NodeAttrTypesExtPtr; // Is not a pointer.
}

/**
 * Free all malloc'd data from the provided attribute through any references it
 * may contain, including child Nodes.
 */
void free_attr(attr_t *attr) {
  if (attr == NULL) {
    return;
  }

  if (attr->type == NodeAttrTypesChildren) {
    node_t **kids = get_children_attr_data(attr);
    int count = attr->data_size / POINTER_SIZE;
    for (int i = 0; i < count; i++) {
      free_node(kids[i]);
    }
  }

  // Function pointers are allocated outside this library.
  if (attr_should_be_freed(attr)) {
    free(attr->data);
  }

  free(attr);
}

/**
 * Recursively free all data from the provided
 * element to it's leaves.
 */
void free_node(node_t *node) {
  for (u32_t i = 0; i < node->attr_count; i++) {
    attr_t *attr = node->attrs[i];
    free_attr(attr);
  }
  free(node->attrs);
  free(node);
}

/**
 * Create and returns a new, empty attribute struct.
 *
 * These entities must be sent to 'free_attr' at some point in the future.
 */
attr_t *new_attr(void) {
  attr_t *attr = malloc(sizeof(attr_t));
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
attr_t *new_char_attr(attr_key_t key, char *value) {
  attr_t *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  if (value == NULL) {
    value = "";
  }
  attr->key = key;
  attr->type = NodeAttrTypesChars;
  attr->data_size = strlen(value) + 1;
  attr->data = (u8_t *)malloc(attr->data_size);
  memcpy(attr->data, value, attr->data_size);
  return attr;
}

/**
 * Get the data from a Char Attr as (char *).
 */
char *get_char_attr_data(attr_t *attr) {
  return (char *)get_attr_data(attr);
}

u8_t *get_attr_data(attr_t *attr) {
  return attr->data;
}

s32_t get_child_count(node_t *node) {
  return node->child_count;
}

/**
 * Create a new Attr with the provided type and s32_t data.
 */
attr_t *new_s32_attr(attr_key_t key, s32_t value) {
  attr_t *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->key = key;
  attr->type = NodeAttrTypesS32;
  attr->data_size = sizeof(s32_t);
  attr->data = malloc(attr->data_size);
  memcpy(attr->data, &value, attr->data_size);
  return attr;
}

/**
 * Get the provided Attribute data as a signed integer.
 */
s32_t get_s32_attr_data(attr_t *attr) {
  return *(s32_t *)get_attr_data(attr);
}

s32_t get_s32_attr_from_node(node_t *node, attr_key_t key,
                                     s32_t default_value) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_s32_attr_data(node->attrs[index]);
  }

  return default_value;
}

/**
 * Create a new Attr with the provided type and u32_t data.
 */
attr_t *new_u32_attr(attr_key_t key, u32_t value) {
  attr_t *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }
  attr->key = key;
  attr->type = NodeAttrTypesU32;
  attr->data_size = sizeof(u32_t);
  attr->data = malloc(attr->data_size);
  memcpy(attr->data, &value, attr->data_size);
  return attr;
}

/**
 * Get the provided Attribute data as an unsigned integer.
 */
u32_t get_u32_attr_data(attr_t *attr) {
  return *(u32_t *)get_attr_data(attr);
}

/**
 * Create a new attribute with an void * pointer value and
 * the provided type.
 */
attr_t *new_ptr_attr(attr_key_t key, void *value) {
  attr_t *attr = new_attr();
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
attr_t *new_ext_ptr_attr(attr_key_t key, void *value) {
  attr_t *attr = new_ptr_attr(key, value);
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
node_t **get_children(node_t *node) {
  s32_t index = get_attr_index_by_key(node, NodeAttrKeysChildren);
  if (index > -1) {
    return get_children_attr_data(node->attrs[index]);
  }

  return NULL;
}

char *get_char_attr_from_node(node_t *node, attr_key_t key,
    char *default_value) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_char_attr_data(node->attrs[index]);
  }

  return default_value;
}

u32_t get_u32_attr_from_node(node_t *node, attr_key_t key,
                                     u32_t default_value) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_u32_attr_data(node->attrs[index]);
  }

  return default_value;
}

u8_t *get_raw_attr_from_node(node_t *node, attr_key_t key) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    attr_t *attr = node->attrs[index];
    return get_attr_data(attr);
  }

  return NULL;
}

/**
 * Create a children Attr.
 */
attr_t *new_children(u32_t count, ...) {
  attr_t *attr = new_attr();
  if (NULL == attr) {
    return NULL;
  }

  attr->type = NodeAttrTypesChildren;
  attr->key = NodeAttrKeysChildren;
  attr->data_size = count * POINTER_SIZE;

  node_t *kids[attr->data_size];

  va_list vargs;
  va_start(vargs, count);
  for (u32_t i = 0; i < count; i++) {
    node_t *kid = va_arg(vargs, node_t *);
    kids[i] = kid;
  }
  va_end(vargs);

  attr->data = (u8_t *)malloc(attr->data_size);
  if (attr->data == NULL) {
    return NULL;
  }
  memcpy(attr->data, kids, attr->data_size);
  return attr;
}

attr_t *children_list(u32_t count, node_t **children) {
  attr_t *attr = new_attr();
  if (attr == NULL) {
    return NULL;
  }

  attr->type = NodeAttrTypesChildren;
  attr->key = NodeAttrKeysChildren;
  attr->data_size = count * POINTER_SIZE;

  attr->data = (u8_t *)malloc(attr->data_size);
  if (attr->data == NULL) {
    free(attr);
    return NULL;
  }
  memcpy(attr->data, children, attr->data_size);
  return attr;
}

/**
 * Get an array of Node pointers as Children data from the provided Attr.
 */
node_t **get_children_attr_data(attr_t *attr) {
  return (node_t **)get_attr_data(attr);
}

/*
static NodeHash hash_node(Node *node) {
  char node_str[1024] = {0};
  node_to_str(node_str, node);
  return fast_hash(node_str, strlen(node_str));
}
*/

/**
 * Create a new Node with the provided attributes.
 */
node_t *new_node(node_type_t type, u32_t attr_count, ...) {
  attr_t **attrs = malloc(attr_count * POINTER_SIZE);
  if (NULL == attrs) {
    return NULL;
  }
  node_t *node = malloc(sizeof(node_t));
  node->id = getNextId();
  node->type = type;
  node->parent_id = 0;
  node->child_count = 0;

  // Process Attrs
  va_list vargs;
  va_start(vargs, attr_count);
  for (u32_t i = 0; i < attr_count; ++i) {
    attr_t *attr = va_arg(vargs, attr_t *);
    if (attr->key == NodeAttrKeysChildren) {
        node->child_count += (attr->data_size / POINTER_SIZE);
        node_t **kids = get_children_attr_data(attr);
        for (u32_t k = 0; k < node->child_count; k++) {
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
void emit_event(node_t *node, attr_key_t key) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    attr_t *attr = node->attrs[index];
    gesture_handler_t gestureHandler = (gesture_handler_t)get_attr_data(attr);
    gestureHandler();
  }
}

/**
 * Return true if the provided Node does not have an assigned parent_id.
 */
bool is_root(node_t *node) {
  return node->parent_id == 0;
}

// static void attr_chars_to_str(char *dest, attr_t *attr) {
//   char *str = {0};
//   sprintf(str, "attr_%d.%s=%s", attr->key, NODE_ATTR_CHARS, attr->data);
//   strcat(dest, str);
// }
//
// static void attr_to_str(char *dest, attr_t *attr, char *indent) {
//   char *str = {0};
//   sprintf(str, "%s attr_%d.type=%d", indent, attr->key, attr->type);
//
//   switch (attr->type) {
//     case NodeAttrTypesChars:
//       attr_chars_to_str(str, attr);
//       break;
//   }
//
//   strcat(dest, str);
// }
//
// static void node_children_to_str(char *dest, node_t *node, char *indent) {
//   node_t **kids = get_children(node);
//   char *str = {0};
//   if (kids != NULL) {
//     char *new_indent = {0};
//     strcat(new_indent, indent);
//     for (u32_t i = 0; i < node->child_count; i++) {
//       node_to_str_indented(str, kids[i], indent);
//     }
//   }
//   strcat(dest, str);
// }
//
// static void node_to_str_indented(char *dest, node_t *node, char *indent) {
//   char *str = {0};
//   sprintf(str, "%s\nnode.type=%d", indent, node->type);
//
//   for (u32_t i = 0; i < node->attr_count; i++) {
//     attr_to_str(str, node->attrs[i], indent);
//   }
//   node_children_to_str(str, node, indent);
//
//   strcat(dest, str);
// }
//
// void node_to_str(char *dest, node_t *node) {
//   char indent[128] = {0};
//   node_to_str_indented(dest, node, indent);
// }
//
// /*
// static size_t node_to_char_len(Node *node) {
//   size_t len = 0;
//   return snprintf(NULL, len, "%d", node->type);
// }
// */
//
// /**
//  * Print the provided node and attributes.
//  */
// void print_node(node_t *node) {
//   char dest[512] = {0};
//   node_to_str(dest, node);
//   printf("%s\n", dest);
// }
