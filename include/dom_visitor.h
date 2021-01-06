#ifndef __dom_visitor_h__
#define __dom_visitor_h__

#include <dom.h>

typedef enum VisitStatus {
  VISIT_SUCCESS = 0,
  VISIT_ABORT,
  VISIT_FAILURE,
	VISIT_MATCHED,
} VisitStatus;

typedef VisitStatus (*VisitHandler)(Node *elem);

VisitStatus each_child(Node *elem, VisitHandler handler);
VisitStatus depth_first(Node *elem, VisitHandler handler);
VisitStatus breadth_first(Node *elem, VisitHandler handler);

Node *find_element_with_matching_char_attr(Node *elem, AttrName name,
		char *value);

#endif // __dom_visitor_h__

