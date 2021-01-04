#include "render.h"
#include <gtk/gtk.h>

GtkWidget *getWidget(Rendered *r) {
  return (GtkWidget *)r->widget;
}

Rendered newRendered(Element *elem) {
}

GtkWidget *newWidget(Element *elem) {
  GtkWidget *widget;
  switch(elem->type) {
    case TypeNone:
      break;
    case TypeBox:
      break;
    case TypeVBox:
      break;
    case TypeHBox:
      break;
    case TypeButton:
      widget = gtk_button_new_with_label("DEFAULT LABEL");
      break;
    case TypeLink:
      break;
    case TypeStyle:
      break;
    case TypeApp:
      break;
    case TypeWindow:
      break;
    case TypeHead:
      break;
    case TypeBody:
      break;
  }

  return widget;
}

