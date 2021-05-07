#include "node_visitor.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**
 * Call visitHandler for each child in the provided node.
 *
 * Does not recurse into child elements.
 */
VisitStatus each_child(Node *node, VisitHandler visitHandler) {
  struct Node **kids = get_children(node);
  for (unsigned int i = 0; i < node->child_count; i++) {
    VisitStatus status = visitHandler(kids[i]);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }
  return VISIT_SUCCESS;
}

/**
 * Call visitHandler for every node that is underneath the provided Node in
 * a depth first traversal.
 *
 * This is generally useful when searching for values that are known to exist on
 * leaf nodes.
 */
VisitStatus depth_first(Node *node, VisitHandler visitHandler) {
  VisitStatus status;
  struct Node **kids = get_children(node);
  for (unsigned int i = 0; i < node->child_count; i++) {
    status = depth_first(kids[i], visitHandler);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  status = visitHandler(node);
  if (status != VISIT_SUCCESS) {
    return status;
  }
  return VISIT_SUCCESS;
}

/**
 * Call visitHandler for every node that is underneath the provided Node in
 * a breadth first traversal.
 *
 * This is generally what people expect when searching the tree for elements
 * with a given attribute value.
 */
VisitStatus breadth_first(Node *node, VisitHandler visitHandler) {
  VisitStatus status = visitHandler(node);
  if (status != VISIT_SUCCESS) {
    return status;
  }

  struct Node **kids = get_children(node);
  for (unsigned int i = 0; i < node->child_count; i++) {
    status = breadth_first(kids[i], visitHandler);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  return VISIT_SUCCESS;
}

// TODO(lbayes): NOT thread safe, need to rework this feature to avoid global values.
static char *matching_value;
static AttrType matching_type;
static Node *matched_node;

static VisitStatus matching_char_visit_handler(Node *node) {
  char *data = get_char_attr_from_node(node, matching_type, "");
  if (strcmp(data, matching_value) == 0) {
    matched_node = node;
    return VISIT_MATCHED;
  }

  return VISIT_SUCCESS;
}

Node *find_element_with_matching_char_attr(Node *node, AttrType type,
    char *value) {
  matched_node = NULL;
  matching_type = type;
  matching_value = value;
  VisitStatus status = breadth_first(node, matching_char_visit_handler);

  if (status == VISIT_MATCHED) {
    return matched_node;
  }
  return NULL;
}

