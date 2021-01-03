#include <gtk/gtk.h>

static gint delete_callback(GtkWidget* w, GdkEventAny* e, gpointer data);
static void button_callback(GtkWidget* w ,gpointer data);

int main(int argc, char* argv[])
{
  GtkWidget* window;
  GtkWidget* button;
  GtkWidget* label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  button = gtk_button_new();
  label = gtk_label_new("Hello World");

  gtk_container_add(GTK_CONTAINER(button),label);
  gtk_container_add(GTK_CONTAINER(window), button);

  gtk_window_set_title(GTK_WINDOW(window), " Hello World");
  gtk_container_set_border_width(GTK_CONTAINER(button),10);
  gtk_window_set_default_size(GTK_WINDOW(window),400,400);

  gtk_signal_connect(GTK_OBJECT(window),
      "delete_event",
      GTK_SIGNAL_FUNC(delete_callback),
      NULL);

  gtk_signal_connect(GTK_OBJECT(button),
      "clicked",
      GTK_SIGNAL_FUNC(button_callback),
      label);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

static gint delete_callback(GtkWidget* w, GdkEventAny* e, gpointer data)
{
  gtk_main_quit();
}

static void button_callback(GtkWidget* w ,gpointer data)
{
  GtkWidget* label;
  gchar* text;

  label = GTK_WIDGET(data);
  gtk_label_get(GTK_LABEL(label), &text);

  printf("%s \n", text);

}

