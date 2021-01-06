#ifndef __dom_visitor_h__
#define __dom_visitor_h__

#include <dom.h>

typedef enum VisitStatus {
  VISIT_SUCCESS = 0,
  VISIT_ABORT,
  VISIT_FAILURE,
	VISIT_MATCHED,
} VisitStatus;

typedef VisitStatus (*VisitHandler)(Element *elem);

VisitStatus each_child(Element *elem, VisitHandler handler);
VisitStatus depth_first(Element *elem, VisitHandler handler);
VisitStatus breadth_first(Element *elem, VisitHandler handler);

Element *find_element_with_matching_char_attr(Element *elem, AttrName name,
		char *value);

#endif // __dom_visitor_h__

