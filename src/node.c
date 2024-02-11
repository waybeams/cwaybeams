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
  for (s32_t i = 0; i < node->attr_count; i++) {
    attr = &node->attrs[i];
    if (attr->key == key) {
      // Prevent index overflow across signed and unsigned integers.
      return i > INT32_MAX ? -1 : i;
    }
  }
  return -1;
}

void *get_attr_data(attr_t *attr) {
  return attr->data;
}

/**
 * Create a new Attr with the provided char value.
 */
attr_t new_char_attr(attr_key_t key, char *value) {
  printf("NEW CHAR ATTR: %d\n", key);
  return (attr_t) {
    .key = key,
    .type = NodeAttrTypesChars,
    .data_size = strlen(value) + 1,
    .data = value,
  };
}

/**
 * Get the data from a Char Attr as (char *).
 */
char *get_char_attr_data(attr_t *attr) {
  return attr->data;
  // return (char *)attr->data;
}

s32_t get_child_count(node_t *node) {
  return (s32_t)node->child_count;
}

/**
 * Create a new Attr with the provided type and s32_t data.
 */
attr_t new_s32_attr(attr_key_t key, s32_t value) {
  attr_t attr = {
    .key = key,
    .type = NodeAttrTypesS32,
    .data_size = sizeof(s32_t),
    .data = (void *)(intptr_t)value
  };
  return attr;
}

/**
 * Get the provided Attribute data as a signed integer.
 */
s32_t get_s32_attr_data(attr_t *attr) {
  return (s32_t)(intptr_t)attr->data;
}

s32_t get_s32_attr_from_node(node_t *node, attr_key_t key,
    s32_t default_value) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_s32_attr_data(&node->attrs[index]);
  }

  return default_value;
}

/**
 * Create a new Attr with the provided type and u32_t data.
 */
attr_t new_u32_attr(attr_key_t key, u32_t value) {
  attr_t attr = {
    .key = key,
    .type = NodeAttrTypesU32,
    .data_size = sizeof(u32_t),
    .data = (void *)(uintptr_t)value,
  };
  return attr;
}

/**
 * Get the provided Attribute data as an unsigned integer.
 */
u32_t get_u32_attr_data(attr_t *attr) {
  return (u32_t)(intptr_t)attr->data;
}

/**
 * Create a new attribute with an void * pointer value and
 * the provided type.
 */
attr_t new_ptr_attr(attr_key_t key, void *value) {
  attr_t attr = {
    .key = key,
    .type = NodeAttrTypesPtr,
    .data_size = POINTER_SIZE,
    .data = value,
  };
  return attr;
}

/**
 * Just like a pointer attribute, but will not be freed
 * by our calls to free_attr().
 */
attr_t new_ext_ptr_attr(attr_key_t key, void *value) {
  attr_t attr = new_ptr_attr(key, value);
  // Replace the type to avoid automatic free calls.
  attr.type = NodeAttrTypesExtPtr;
  return attr;
}

/**
 * Get the provided Node children collection.
 */
node_t *get_children(node_t *node) {
  s32_t index = get_attr_index_by_key(node, NodeAttrKeysChildren);
  if (index > -1) {
    return get_children_attr_data(&node->attrs[index]);
  }

  return NULL;
}

char *get_char_attr_from_node(node_t *node, attr_key_t key,
    char *default_value) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_char_attr_data(&node->attrs[index]);
  }

  return default_value;
}

u32_t get_u32_attr_from_node(node_t *node, attr_key_t key,
                                     u32_t default_value) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return get_u32_attr_data(&node->attrs[index]);
  }

  return default_value;
}

attr_t *get_attr(node_t *node, attr_key_t key) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    return &node->attrs[index];
  }

  return NULL;
}

void *get_raw_attr_data_from_node(node_t *node, attr_key_t key) {
  attr_t *attr = get_attr(node, key);
  if (attr != NULL) {
    return attr->data;
  }

  return NULL;
}

/**
 * Create a children Attr.
 */
attr_t new_children(u32_t count, ...) {
  attr_t attr = {
    .type = NodeAttrTypesChildren,
    .key = NodeAttrKeysChildren,
    .data_size = count * POINTER_SIZE,
    .data = NULL,
  };

  // node_t *kids[attr->data_size];
  va_list vargs;
  va_start(vargs, count);
  // for (u32_t i = 0; i < count; i++) {
  //   node_t *kid = va_arg(vargs, node_t *);
  //   kids[i] = kid;
  // }
  attr.data = (void *)vargs;
  va_end(vargs);

  // attr->data = (u8_t *)malloc(attr->data_size);
  // if (attr->data == NULL) {
  //   return NULL;
  // }
  // memcpy(attr->data, kids, attr->data_size);
  return attr;
}

attr_t children_list(u32_t count, node_t *children) {
  attr_t attr = {
    .type = NodeAttrTypesChildren,
    .key = NodeAttrKeysChildren,
    .data_size = count * POINTER_SIZE,
    .data = (void *)children,
  };
  return attr;
}

/**
 * Get an array of Node pointers as Children data from the provided Attr.
 */
node_t *get_children_attr_data(attr_t *attr) {
  return (node_t *)attr->data;
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
node_t new_node(node_type_t type, u32_t attr_count, ...) {
  attr_t *attrs = calloc(0, attr_count * sizeof(attr_t));

  node_t node = {
    .id = getNextId(),
    .type = type,
    .attr_count = attr_count,
    .attrs = attrs,
  };

  // Process Attrs
  va_list vargs;
  va_start(vargs, attr_count);
  // node.attrs = (attr_t *)vargs;
  for (u32_t i = 0; i < attr_count; ++i) {
     attr_t attr = va_arg(vargs, attr_t);

     // if (attr->key == NodeAttrKeysChildren) {
     //     node.child_count += (attr->data_size / POINTER_SIZE);
     //     node_t *kids = get_children_attr_data(attr);
     //     for (u32_t k = 0; k < node.child_count; k++) {
     //         kids[k].parent_id = node.id;
     //     }
     // }
     memcpy(&node.attrs[i], &attr, sizeof(attr_t));
  }
  va_end(vargs);
  // node.hash = hash_node(node);
  printf("-----------------------------\n");
  return node;
}

/**
 * Call any handlers found for the provided gesture type.
 */
void emit_event(node_t *node, attr_key_t key) {
  s32_t index = get_attr_index_by_key(node, key);
  if (index > -1) {
    attr_t *attr = &node->attrs[index];
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

void free_node(node_t *node) {
  free(node->attrs);
  // free(node);
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
