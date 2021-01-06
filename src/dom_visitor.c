#include "dom_visitor.h"
#include "dom.h"

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

VisitStatus depth_first(Element *elem, VisitHandler visitHandler) {
  struct Element **kids = getChildren(elem);
  for (int i = 0; i < elem->childCount; i++) {
    depth_first(kids[i], visitHandler);
    VisitStatus status = visitHandler(kids[i]);
    if (status != VISIT_SUCCESS) {
      return status;
    }
  }
  return VISIT_SUCCESS;
}


