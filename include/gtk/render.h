#ifndef __GTK_RENDER_H__
#define __GTK_RENDER_H__

#include <gtk/gtk.h>

typedef struct GtkRenderContext {
  GApplication *application;
  GtkWidget *window;
} GtkRenderContext;

#endif // __GTK_RENDER_H__
