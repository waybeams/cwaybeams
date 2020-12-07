#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;

static Element *pendingElement;

static void resetPendingElement() {
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

void printElement(Element *elem, uint8_t depth) {
  char tabs[20] = "\0";
  printf("depth: %d\n", depth);
  for (int i = 0; i < depth; i++) {
    strcat(tabs, "\t");
  }

  printf("%sid: %d\n", tabs, elem->id);
  printf("%sname: %s\n", tabs, elem->name);
  printf("%saddr: %p\n", tabs, elem);
  printf("%sparentId: %d\n", tabs, elem->parentId);
  printf("%slayout: %d\n", tabs, elem->layout);
  printf("%swidth: %d\n", tabs, elem->width);
  printf("%sheight: %d\n", tabs, elem->height);
  printf("%schildCount: %d\n", tabs, elem->childCount);
  for (int i = 0; i < elem->childCount; i++) {
    Element *child = &elem->children[i];
    printf("%s>> child[%d].id: %d\n", tabs, i, child->id);
    printElement(child, depth + 1);
  }
  printf("%s-----------------\n", tabs);
}

Element* container(Context *ctx, Layout layout) {
  Element *elem;
  elem = malloc(sizeof(Element));
  if (elem == NULL) {
    return NULL;
  }
  copyElement(elem, pendingElement);

  elem->id = lastId++;
  if (elem->layout == LAYOUT_DEFAULT) {
    elem->layout = layout;
  }

  resetPendingElement();
  // printElement(elem, 0);
  // printf("elem %d\n", elem->id);
  return elem;
}

uint8_t children(Context *ctx, unsigned int count, ...) {
  va_list vargs;
  Element *kids;
  kids = malloc(count * sizeof(Element));

  va_start(vargs, count);
  for (int i = 0; i < count; i++) {
    kids[i] = *va_arg(vargs, Element*);
  }

  va_end(vargs);

  pendingElement->children = kids;
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
