#ifndef __render_h__
#define __render_h__

typedef struct Rendered {
  Node *node;
  unsigned char *widget;
}Rendered;

Rendered *render(Node *node);

#endif // __render_h__
