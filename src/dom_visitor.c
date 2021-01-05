#include "dom_visitor.h"
#include "dom.h"

VisitStatus each_child(Element *elem, VisitHandler handler) {
  struct Element **kids = getChildren(elem);
  for (int i = 0; i < elem->childCount; i++) {
    VisitStatus status = handler(kids[i]);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }
  return VISIT_SUCCESS;
}

VisitStatus depth_first(Element *elem, VisitHandler handler) {
  struct Element **kids = getChildren(elem);
  for (int i = 0; i < elem->childCount; i++) {
    depth_first(kids[i], handler);
    VisitStatus status = handler(kids[i]);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }
  return VISIT_SUCCESS;
  return VISIT_SUCCESS;
}
