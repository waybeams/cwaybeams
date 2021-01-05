#ifndef __dom_visitor_h__
#define __dom_visitor_h__

#include <dom.h>

typedef enum VisitStatus {
  VISIT_SUCCESS = 0,
  VISIT_ABORT,
  VISIT_FAILURE,
} VisitStatus;

typedef VisitStatus (*VisitHandler)(Element *elem);

VisitStatus depth_first(Element *elem, VisitHandler handler);

VisitStatus each_child(Element *elem, VisitHandler handler);

#endif // __dom_visitor_h__

