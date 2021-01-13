#include "render.h"
#include "box.h"
#include <gtk/gtk.h>
#include <stdlib.h>


GtkWidget *widget_from_node(Node *node);

Rendered *render(Node *node) {
  Rendered *r = malloc(sizeof(Rendered));
  r->node = node;
  r->widget = (unsigned char *)widget_from_node(node);
  return r;
}

GtkWidget *render_button(Node *node) {
  return gtk_button_new_with_label(get_label(node));
}

static void on_app_activate(GApplication *app, gpointer data) {
    // create a new application window for the application
    // GtkApplication is sub-class of GApplication
    // downcast GApplication* to GtkApplication* with GTK_APPLICATION() macro
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_widget_set_size_request(window, 1024, 768);

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


GtkWidget *render_window(Node *node) {
  // GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
  // gtk_widget_set_size_request(window, 1024, 768);
  // return window;
  return NULL;
}

GtkWidget *render_app(Node *node) {
  GtkApplication *app = gtk_application_new(
      "org.gtkmm.example.HelloApp",
      G_APPLICATION_FLAGS_NONE
  );
  if (app == NULL) {
    return NULL;
  }

  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  return (GtkWidget *)app;
}

  // start the application, terminate by closing the window
  // GtkApplication* is upcast to GApplication* with G_APPLICATION() macro
  // int status = g_application_run(G_APPLICATION(app), argc, argv);
  // deallocate the application object
  // g_object_unref(app);

GtkWidget *widget_from_node(Node *node) {
  GtkWidget *widget;
  switch(node->type) {
    case BoxTypeNone:
      break;
    case BoxTypeApp:
      return render_app(node);
      break;
    case BoxTypeBox:
      break;
    case BoxTypeVBox:
      break;
    case BoxTypeHBox:
      break;
    case BoxTypeButton:
      return render_button(node);
    case BoxTypeLink:
      break;
    case BoxTypeStyle:
      break;
    case BoxTypeWindow:
      return render_window(node);
    case BoxTypeHead:
      break;
    case BoxTypeBody:
      break;
  }

  return NULL;
}

