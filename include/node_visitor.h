#ifndef __node_visitor_h__
#define __node_visitor_h__

#include "node.h"

typedef enum {
  VISIT_SUCCESS = 0,
  VISIT_ABORT,
  VISIT_FAILURE,
	VISIT_MATCHED,
} visit_status_t;

typedef visit_status_t (*visit_handler_t)(node_t *node, void *payload);

/**
 * Call visitHandler for each child in the provided node.
 *
 * Does not recurse into child elements.
 */
visit_status_t each_child(node_t *node, visit_handler_t visit_handler,
    void *payload);

/**
 * Call visitHandler for every node that is underneath the provided Node in
 * a depth first traversal.
 *
 * This is generally useful when searching for values that are known to exist on
 * leaf nodes.
 */
visit_status_t depth_first(node_t *node, visit_handler_t handler,
    void *payload);

/**
 * Call visitHandler for every node that is underneath the provided Node in
 * a breadth first traversal.
 *
 * This is generally what people expect when searching the tree for elements
 * with a given attribute value.
 */
visit_status_t breadth_first(node_t *node, visit_handler_t handler,
    void *payload);

/**
 * Find the first node that has an attribute with the given type and value.
 */
node_t *find_element_with_matching_char_attr(node_t *node, attr_type_t type,
    char *value, void *payload);

#endif // __node_visitor_h__

