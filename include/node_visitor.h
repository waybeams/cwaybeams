#ifndef __node_visitor_h__
#define __node_visitor_h__

#include "node.h"

typedef enum {
  VISIT_SUCCESS = 0,
  VISIT_ABORT,
  VISIT_FAILURE,
	VISIT_MATCHED,
} visit_status_t;

typedef visit_status_t (*visit_handler_t)(node_t *node);

visit_status_t each_child(node_t *node, visit_handler_t visit_handler);
visit_status_t depth_first(node_t *node, visit_handler_t handler);
visit_status_t breadth_first(node_t *node, visit_handler_t handler);

node_t *find_element_with_matching_char_attr(node_t *node, attr_type_t type,
                                             char *value);

#endif // __node_visitor_h__

