#ifndef __node_h__
#define __node_h__

#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include "fast_hash.h"

#define DEFAULT_ZERO 0
#define DEFAULT_CHAR ""

#define NODE_ATTR_CHILDREN 1
#define NODE_ATTR_HANDLER 2

typedef unsigned int NodeAttr;
typedef unsigned int NodeType;
typedef unsigned long NodeId;
typedef uint32_t NodeHash;
typedef void (*GestureHandler)(void);

typedef enum NodeAttrs {
  NodeAttrNone = 0,
  NodeAttrChildren,
  NodeAttrName,
  NodeAttrFunction = 500,
} NodeAttrs;

typedef enum NodeTypes {
  NodeTypeNode = 0,
} NodeTypes;

/**
 * Container for arbitrary data
 * values.
 */
typedef struct Attr {
  NodeAttr type;
  unsigned int data_size;
  unsigned char *data;
} Attr;

typedef struct Node {
  NodeId id;
  NodeId parent_id;
  NodeHash hash;
  NodeType type;
  unsigned int child_count;
  unsigned int attr_count;
  struct Attr **attrs;
} Node;


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
Node *new_node(NodeType type, unsigned int count, ...);
Attr *new_attr(void);
Attr *new_children(unsigned int count, ...);

// Attribute type factories
Attr *new_char_attr(NodeAttr type, char *value);
Attr *new_uint_attr(NodeAttr type, unsigned value);
Attr *new_ptr_attr(NodeAttr type, unsigned char *value);

// Attribute type getters
unsigned char *get_attr_data(Attr *attr);
struct Node **get_nodes_attr(Attr *attr);
unsigned int get_uint_attr_data(Attr *attr);
char *get_char_attr_data(Attr *attr);


// Node Attribute getters
struct Node **get_children(Node *node);

// Node helpers
void print_node(Node *node);
bool is_root(Node *node);
void emit_event(Node *node, char *gesture_name);

// Destructors
void free_node(Node *node);
void free_attr(Attr *attr);

// Used by Macros only
char *get_char_attr_from_node(Node *node, NodeAttr type, char *default_value);
unsigned int get_uint_attr_from_node(Node *node, NodeAttr type,
    unsigned int default_value);
unsigned char *get_raw_attr_from_node(Node *node, NodeAttr type);

#endif // __node_h__
