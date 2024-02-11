#ifndef __node_h__
#define __node_h__

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DEFAULT_ZERO 0
#define DEFAULT_CHAR ""

/**
 * Node is the central composable and configurable type for constructing trees
 * that represent a variety of data structures, including user interface
 * elements.
 */

#ifndef u8_t
typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;
typedef int8_t s8_t;
typedef int16_t s16_t;
typedef int32_t s32_t;
typedef int64_t s64_t;
typedef float f32_t;
typedef double f64_t;
typedef s8_t q7_t;
typedef s16_t q15_t;
typedef s32_t q31_t;
typedef s64_t q63_t;
#endif

typedef u16_t attr_type_t;
typedef u16_t attr_key_t;
typedef u16_t node_type_t;
typedef unsigned long node_id_t;
typedef u32_t node_hash_t;
typedef void (*gesture_handler_t)(void);

#define NODE_ATTR_CHILDREN "children"
#define NODE_ATTR_CHARS "chars"
#define NODE_ATTR_CHARS_LEN strlen(NODE_ATTR_CHARS)
#define NODE_ATTR_U32 "u32"
#define NODE_ATTR_S32 "s32"
#define NODE_ATTR_PTR "ptr"
#define NODE_ATTR_EXT_PTR "extptr"

typedef enum node_attr_types {
  NodeAttrTypeNone = 0,
  NodeAttrTypesChildren,
  NodeAttrTypesChars,
  NodeAttrTypesU32,
  NodeAttrTypesS32,
  NodeAttrTypesPtr,
  NodeAttrTypesExtPtr,
} node_attr_types;

typedef enum node_attr_keys {
  NodeAttrKeysNone = 0,
  NodeAttrKeysChildren,
  NodeAttrKeysLast = 100,
} node_attr_keys;

typedef enum node_types {
  NodeTypeNode = 0,
} node_types;

/**
 * Container for arbitrary data
 * values.
 */
typedef struct attr_t {
  attr_key_t key;
  attr_type_t type;
  u16_t data_size;
  void *data;
} attr_t;

/**
 * Base type for building a tree
 */
typedef struct node_t {
  node_id_t id;
  node_id_t parent_id;
  node_hash_t hash;
  node_type_t type;
  u32_t child_count;
  u32_t attr_count;
  attr_t *attrs;
} node_t;

#define PP_ARG_N( \
          _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, N, ...) N

/* Note 63 is removed */
#define PP_RSEQ_N()                                        \
         62, 61, 60,                                       \
         59, 58, 57, 56, 55, 54, 53, 52, 51, 50,           \
         49, 48, 47, 46, 45, 44, 43, 42, 41, 40,           \
         39, 38, 37, 36, 35, 34, 33, 32, 31, 30,           \
         29, 28, 27, 26, 25, 24, 23, 22, 21, 20,           \
         19, 18, 17, 16, 15, 14, 13, 12, 11, 10,           \
          9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define PP_NARG_(...)    PP_ARG_N(__VA_ARGS__)

/* Note dummy first argument _ and ##__VA_ARGS__ instead of __VA_ARGS__ */
#define PP_NARG(...)     PP_NARG_(_, ##__VA_ARGS__, PP_RSEQ_N())

#define node(...) new_node(NodeTypeNode, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define children(...) new_children(PP_NARG(__VA_ARGS__), __VA_ARGS__)

// Attribute custom factories
node_t new_node(node_type_t type, u32_t count, ...);
attr_t new_children(u32_t count, ...);
attr_t children_list(u32_t count, node_t *children);

// Attribute type factories
attr_t new_char_attr(attr_key_t key, char *value);
attr_t new_u32_attr(attr_key_t key, u32_t value);
attr_t new_s32_attr(attr_key_t key, s32_t value);
attr_t new_ptr_attr(attr_key_t key, void *value);
attr_t new_ext_ptr_attr(attr_key_t key, void *value);

// Attribute type getters
s32_t get_child_count(node_t *node);
u32_t get_u32_attr_data(attr_t *attr);
s32_t get_s32_attr_data(attr_t *attr);

void *get_attr_data(attr_t *attr);
node_t *get_children_attr_data(attr_t *attr);
char *get_char_attr_data(attr_t *attr);

// Node Attribute getters
node_t *get_children(node_t *node);

// Node helpers
void print_node(node_t *node);
// void node_to_str(char *dest, node_t *node);
bool is_root(node_t *node);
void emit_event(node_t *node, attr_key_t key);
attr_t *get_attr(node_t *node, attr_key_t key);

// Used by Macros only
char *get_char_attr_from_node(node_t *node, attr_type_t type,
    char *default_value);
u32_t get_u32_attr_from_node(node_t *node, attr_type_t type,
    u32_t default_value);
s32_t get_s32_attr_from_node(node_t *node, attr_type_t type,
    s32_t default_value);
void *get_raw_attr_data_from_node(node_t *node, attr_type_t type);

#endif // __node_h__
