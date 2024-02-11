#include "node_visitor.h"
#include "shared.h"
#include <stddef.h>
#include <string.h>

visit_status_t each_child(node_t *node, visit_handler_t visit_handler,
    void *payload) {
  node_t *kids = get_children(node);
  for (u32_t i = 0; i < node->child_count; i++) {
    node_t *kid = &kids[i];
    visit_status_t status = visit_handler(kid, payload);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }
  return VISIT_SUCCESS;
}

visit_status_t depth_first(node_t *node, visit_handler_t visitHandler,
    void *payload) {
  visit_status_t status;
  node_t *kids = get_children(node);
  for (u32_t i = 0; i < node->child_count; i++) {
    status = depth_first(&kids[i], visitHandler, payload);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  status = visitHandler(node, payload);
  if (status != VISIT_SUCCESS) {
    return status;
  }
  return VISIT_SUCCESS;
}

visit_status_t breadth_first(node_t *node, visit_handler_t visitHandler,
    void *payload) {
  visit_status_t status = visitHandler(node, payload);
  if (status != VISIT_SUCCESS) {
    return status;
  }

  node_t *kids = get_children(node);
  for (u32_t i = 0; i < node->child_count; i++) {
    status = breadth_first(&kids[i], visitHandler, payload);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  return VISIT_SUCCESS;
}

// TODO(lbayes): NOT thread safe, need to rework this feature to avoid global values.
static char *matching_value;
static attr_type_t matching_type;
static node_t *matched_node;

static visit_status_t matching_char_visit_handler(node_t *node,
    UNUSED void *payload) {
  char *data = get_char_attr_from_node(node, matching_type, "");
  if (strcmp(data, matching_value) == 0) {
    matched_node = node;
    return VISIT_MATCHED;
  }

  return VISIT_SUCCESS;
}

node_t *find_element_with_matching_char_attr(node_t *node, attr_type_t type,
    char *value, void *payload) {
  matched_node = NULL;
  matching_type = type;
  matching_value = value;
  visit_status_t status = breadth_first(node, matching_char_visit_handler,
                                        payload);

  if (status == VISIT_MATCHED) {
    return matched_node;
  }
  return NULL;
}

