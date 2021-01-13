#ifndef __render_h__
#define __render_h__

#include "node.h"

typedef struct Rendered {
  Node *node;
  unsigned char *widget;
} Rendered;

Rendered *render(Node *node);
int new_app(int argc, char *argv[]);
int exec_app(Node *app, int argc, char *argv[]);

#endif // __render_h__
