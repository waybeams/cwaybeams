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

GtkWidget *widget_from_node(Node *node) {
  GtkWidget *widget;
  switch(node->type) {
    case BoxTypeNone:
      break;
    case BoxTypeBox:
      break;
    case BoxTypeVBox:
      break;
    case BoxTypeHBox:
      break;
    case BoxTypeButton:
      widget = gtk_button_new_with_label(get_label(node));
      break;
    case BoxTypeLink:
      break;
    case BoxTypeStyle:
      break;
    case BoxTypeApp:
      break;
    case BoxTypeWindow:
      break;
    case BoxTypeHead:
      break;
    case BoxTypeBody:
      break;
  }

  return widget;
}

