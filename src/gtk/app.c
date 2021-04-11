#include "box.h"
#include "gtk/render.h"
#include "render.h"
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>

static char *btn_label_one = "Label One";
static char *btn_label_two = "Label Two";
static char *btn_label;

GtkWidget *get_widget(Rendered *r) {
  return (GtkWidget *)r->widget;
}


// callback function which is called when button is clicked
static void on_button_clicked(GtkButton *btn, gpointer data) {
    // change button label when it's clicked
    if (strcmp(btn_label, btn_label_one) == 0) {
      btn_label = btn_label_two;
    } else {
      btn_label = btn_label_one;
    }
    gtk_button_set_label(btn, btn_label);
}

// callback function which is called when application is first started
static void on_app_activate(GApplication *app, gpointer data) {
    printf("on_app_activate\n");
    btn_label = btn_label_one;

    // create a new application window for the application
    // GtkApplication is sub-class of GApplication
    // downcast GApplication* to GtkApplication* with GTK_APPLICATION() macro
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_widget_set_size_request(window, 1024, 768);

    GtkWidget *fixedContainer = gtk_fixed_new();

    // a simple push button
    GtkWidget *btn = gtk_button_new_with_label("Click Me!");
    gtk_widget_set_size_request(btn, 200, 60);

    // connect the event-handler for "clicked" signal of button
    g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clicked), NULL);

    Node *b = button(label("Hello World"));
    GtkRenderContext *c = malloc(sizeof(GtkRenderContext));
    if (c == NULL) {
      printf("Failed to initialize GtkRenderContext");
      exit(1);
    }

    Rendered *r = render(b, c);
    GtkWidget *w = get_widget(r);

    gtk_container_add(GTK_CONTAINER(fixedContainer), w);

    // add the button to the window
    // gtk_container_add(GTK_CONTAINER(fixedContainer), btn);
    gtk_container_add(GTK_CONTAINER(window), fixedContainer);
    // display the window
    gtk_widget_show_all(GTK_WIDGET(window));
}

int new_app_old(int argc, char *argv[]) {
    // create new GtkApplication with an unique application ID
    GtkApplication *app = gtk_application_new(
        "org.gtkmm.example.HelloApp",
        G_APPLICATION_FLAGS_NONE
    );
    // connect the event-handler for "activate" signal of GApplication
    // G_CALLBACK() macro is used to cast the callback function pointer
    // to generic void pointer
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
    // start the application, terminate by closing the window
    // GtkApplication* is upcast to GApplication* with G_APPLICATION() macro
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // deallocate the application object
    g_object_unref(app);
    return status;
}

Node *new_app_node() {
  return app(
    children(
      window(
        children(
          button(label("Hello"))
        )
      )
    )
  );
}

int new_app(int argc, char *argv[]) {
  Node *node = new_app_node();

  GtkRenderContext *c = malloc(sizeof(GtkRenderContext));
  if (c == NULL) {
    printf("Failed to initialize GtkRenderContext");
    exit(1);
  }

  Rendered *r = render(node, c);
  return application_run(c->application, argc, argv);
}
