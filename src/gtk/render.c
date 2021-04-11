#include "box.h"
#include "gtk/render.h"
#include "render.h"
#include <gtk/gtk.h>
#include <stdlib.h>

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768

GtkWidget *widget_from_node(Node *node, GtkRenderContext *c);

Rendered *render(Node *node, void *context) {
  GtkRenderContext *c = (GtkRenderContext*)context;
  Rendered *r = malloc(sizeof(Rendered));
  r->node = node;
  r->widget = (unsigned char *)widget_from_node(node, c);
  r->context = c;
  return r;
}

GtkWidget *render_button(Node *node, GtkRenderContext *c) {
  return gtk_button_new_with_label(get_label(node));
}

static void on_app_activate(GApplication *app, gpointer data) {
    // create a new application window for the application
    // GtkApplication is sub-class of GApplication
    // downcast GApplication* to GtkApplication* with GTK_APPLICATION() macro
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    // gtk_widget_set_size_request(window, 1024, 768);

    GtkWidget *fixedContainer = gtk_fixed_new();

    // a simple push button
    // GtkWidget *btn = gtk_button_new_with_label("Click Me!");
    // gtk_widget_set_size_request(btn, 200, 60);

    // connect the event-handler for "clicked" signal of button
    // g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Node *b = button(label("Hello World"));
    // Rendered *r = render(b);
    // GtkWidget *w = get_widget(r);

    // gtk_container_add(GTK_CONTAINER(fixedContainer), w);

    // add the button to the window
    // gtk_container_add(GTK_CONTAINER(fixedContainer), btn);
    // gtk_container_add(GTK_CONTAINER(window), fixedContainer);
    // display the window
    // gtk_widget_show_all(GTK_WIDGET(window));
}

GtkWidget *render_window(Node *node, GtkRenderContext *c) {
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(c->application));
  unsigned int width = get_width(node);
  if (width == 0) {
    width = DEFAULT_WINDOW_WIDTH;
  }
  unsigned int height = get_height(node);
  if (height == 0) {
    height = DEFAULT_WINDOW_HEIGHT;
  }
  gtk_widget_set_size_request(window, width, height);
  c->window = window;
  return window;
}

GtkWidget *render_app(Node *node, GtkRenderContext *c) {
  GtkApplication *app = gtk_application_new(
      "org.gtkmm.example.HelloApp",
      G_APPLICATION_FLAGS_NONE
  );

  if (app == NULL) {
    return NULL;
  }

  c->application = app;
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  return (GtkWidget *)app;
}

int application_run(GtkApplication *app, int argc, char *argv[]) {
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}

GtkWidget *widget_from_node(Node *node, GtkRenderContext *c) {
  printf("widget_from_node with: %d\n", node->type);
  GtkWidget *widget;

  switch(node->type) {
    case BoxTypeNone:
      break;
    case BoxTypeApp:
      return render_app(node, c);
      break;
    case BoxTypeBox:
      break;
    case BoxTypeVBox:
      break;
    case BoxTypeHBox:
      break;
    case BoxTypeButton:
      return render_button(node, c);
    case BoxTypeLink:
      break;
    case BoxTypeStyle:
      break;
    case BoxTypeWindow:
      return render_window(node, c);
    case BoxTypeHead:
      break;
    case BoxTypeBody:
      break;
  }

  return NULL;
}

