#ifndef __render_h__
#define __render_h__

typedef struct Rendered {
  Element *element;
  unsigned char *widget;
}Rendered;

Rendered *render(Element *elem);

#endif // __render_h__