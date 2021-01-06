#ifndef __render_h__
#define __render_h__

typedef struct Rendered {
  Node *element;
  unsigned char *widget;
}Rendered;

Rendered *render(Node *elem);

#endif // __render_h__
