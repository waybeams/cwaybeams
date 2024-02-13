#ifndef __render_h__
#define __render_h__

#include "node.h"
#include "beam.h"

typedef node_t *(AppRenderer)(BoxServices *s);

typedef struct Rendered {
  node_t *node;
  unsigned char *widget;
  void *context;
} Rendered;

Rendered *render(node_t *node, void *context);
int exec_app(AppRenderer r, BoxServices *s);

#endif // __render_h__
