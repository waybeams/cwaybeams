#ifndef __render_h__
#define __render_h__

#include "node.h"
#include "box.h"

typedef Node *(*AppRenderer)(BoxServices *s);

typedef struct Rendered {
  Node *node;
  unsigned char *widget;
} Rendered;

Rendered *render(Node *node, void *context);
int exec_app(AppRenderer r, BoxServices *s);

#endif // __render_h__
