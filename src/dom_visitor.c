#include "dom_visitor.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**
 * Call visitHandler for each child in the provided element.
 *
 * Does not recurse into child elements.
 */
VisitStatus each_child(Node *elem, VisitHandler visitHandler) {
  struct Node **kids = getChildren(elem);
  for (int i = 0; i < elem->child_count; i++) {
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
VisitStatus depth_first(Node *elem, VisitHandler visitHandler) {
  VisitStatus status;
  struct Node **kids = getChildren(elem);
  for (int i = 0; i < elem->child_count; i++) {
    status = depth_first(kids[i], visitHandler);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  status = visitHandler(elem);
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
VisitStatus breadth_first(Node *elem, VisitHandler visitHandler) {
  VisitStatus status = visitHandler(elem);
  if (status != VISIT_SUCCESS) {
    return status;
  }

  struct Node **kids = getChildren(elem);
  for (int i = 0; i < elem->child_count; i++) {
    status = breadth_first(kids[i], visitHandler);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  return VISIT_SUCCESS;
}

// TODO(lbayes): NOT thread safe, need to rework this feature to avoid global values.
static char *matching_value;
static AttrName matching_name;
static Node *matched_elem;

static VisitStatus matching_char_visit_handler(Node *elem) {
  char *data = getCharAttrFromNode(elem, matching_name, "");
  if (strcmp(data, matching_value) == 0) {
    matched_elem = elem;
    return VISIT_MATCHED;
  }

  return VISIT_SUCCESS;
}

Node *find_element_with_matching_char_attr(Node *elem, AttrName name,
    char *value) {
  matched_elem = NULL;
  matching_name = name;
  matching_value = value;
  VisitStatus status = breadth_first(elem, matching_char_visit_handler);

  if (status == VISIT_MATCHED) {
    return matched_elem;
  }
  return NULL;
}
