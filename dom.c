#include "dom.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static ElementId lastId = 1;

static Element *pendingElement;

void resetPendingElement() {
  free(pendingElement);
  pendingElement = NULL;
  pendingElement = malloc(sizeof(Element));
  pendingElement->childCount = 0;
  pendingElement->id = 0;
  pendingElement->name = "";
  pendingElement->width = 0;
  pendingElement->height = 0;
}

void copyElement(Element *target, Element *source) {
  target->id = source->id;
  target->height = source->height;
  target->name = source->name;
  target->width = source->width;
  target->childCount = source->childCount;
  target->children = source->children;
}

void printElement(Element *elem) {
  printf("addr: %p\n", elem);
  printf("id: %d\n", elem->id);
  printf("parentId: %d\n", elem->parentId);
  printf("name: %s\n", elem->name);
  printf("layout: %d\n", elem->layout);
  printf("width: %d\n", elem->width);
  printf("height: %d\n", elem->height);
  printf("childCount: %d\n", elem->childCount);
  for (int i = 0; i < elem->childCount; i++) {
    Element *child = &elem->children[i];
    printf(" >> child[%d].id: %d\n", i, child->id);
  }
  printf("-----------------\n");
}

Element* container(Context *ctx, Layout layout) {
  Element *elem;
  elem = malloc(sizeof(Element));
  copyElement(elem, pendingElement);

  elem->id = lastId++;
  if (elem->layout == LAYOUT_DEFAULT) {
    elem->layout = layout;
  }

  resetPendingElement();
  printElement(elem);
  return elem;
}

uint8_t children(Context *ctx, unsigned int count, ...) {
  va_list kids;
  printf(">>>>>>> children count %d\n", count);
  Element children[count];
  va_start(kids, count);
  Element *child;
  for (int i = 0; i < count; i++) {
    child = va_arg(kids, Element*);
    printf("CHILD ID: %d\n", child->id);
    children[i] = *child;
  }

  va_end(kids);

  pendingElement->children = children;
  pendingElement->childCount = count;
  return 0;
}

Element* vbox(Context *ctx, ...) {
  return container(ctx, LAYOUT_VERTICAL);
}

Element* hbox(Context *ctx, ...) {
  return container(ctx, LAYOUT_HORIZONTAL);
}

Element* box(Context *ctx, ...) {
  return container(ctx, LAYOUT_STACK);
}

uint8_t name(Context *ctx, char *n) {
  // printf("name: %s\n", n);
  pendingElement->name = n;
  return 0;
}

uint8_t width(Context *ctx, unsigned int w) {
  // printf("width: %d\n", w);
  pendingElement->width = w;
  return 0;
}

uint8_t height(Context *ctx, unsigned int h) {
  // printf("height: %d\n", h);
  pendingElement->height = h;
  return 0;
}

void begin(Context *ctx) {
  resetPendingElement();
}

void end(Context *ctx) {
  resetPendingElement();
}
