#ifndef __GTK_RENDER_H__
#define __GTK_RENDER_H__

#include <gtk/gtk.h>

typedef struct GtkRenderContext {
  GtkApplication *application;
  GtkWidget *window;
} GtkRenderContext;

int application_run(GtkApplication *app, int argc, char *argv[]);

#endif // __GTK_RENDER_H__
