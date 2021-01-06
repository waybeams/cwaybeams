#include "dom_visitor.h"
#include "dom.h"

/**
 * Call visitHandler for each child in the provided element.
 *
 * Does not recurse into child elements.
 */
VisitStatus each_child(Element *elem, VisitHandler visitHandler) {
  struct Element **kids = getChildren(elem);
  for (int i = 0; i < elem->childCount; i++) {
    VisitStatus status = visitHandler(kids[i]);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }
  return VISIT_SUCCESS;
}

/**
 * Call visitHandler for every node that is underneath the provided Element in
 * a depth first traversal.
 *
 * This is generally useful when searching for values that are known to exist on
 * leaf nodes.
 */
VisitStatus depth_first(Element *elem, VisitHandler visitHandler) {
  VisitStatus status;
  struct Element **kids = getChildren(elem);
  for (int i = 0; i < elem->childCount; i++) {
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
 * Call visitHandler for every node that is underneath the provided Element in
 * a breadth first traversal.
 *
 * This is generally what people expect when searching the tree for elements
 * with a given attribute value.
 */
VisitStatus breadth_first(Element *elem, VisitHandler visitHandler) {
  VisitStatus status = visitHandler(elem);
  if (status != VISIT_SUCCESS) {
    return status;
  }

  struct Element **kids = getChildren(elem);
  for (int i = 0; i < elem->childCount; i++) {
    status = breadth_first(kids[i], visitHandler);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }

  return VISIT_SUCCESS;
}

