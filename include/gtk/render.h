#ifndef __GTK_RENDER_H__
#define __GTK_RENDER_H__

#include <gtk/gtk.h>

typedef struct GtkRenderContext {
  GtkApplication *application;
  GtkWidget *window;
  int argc;
  char *argv[];
} GtkRenderContext;

typedef Node* (new_nodes_t)(void *);

int run(int argc, char *argv[], new_nodes_t new_nodes);

#endif // __GTK_RENDER_H__
