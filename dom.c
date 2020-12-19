#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;

static void resetPendingElement(Context *ctx) {
  free(ctx->pending);
  // ctx->pending = NULL;
  Element *pending = malloc(sizeof(Element));
  pending->childCount = 0;
  pending->id = 0;
  pending->name = "";
  pending->width = 0;
  pending->height = 0;
  ctx->pending = pending;
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

  // printf("%sname: %s layout: %d\n", tabs, elem->name, elem->layout);
  printf("%sid: %d parent: %d addr: %p\n", tabs, elem->id, elem->parentId, elem);
  printf("%sw: %d h: %d\n", tabs, elem->width, elem->height);
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
  copyElement(elem, ctx->pending);

  elem->id = lastId++;
  if (elem->layout == LAYOUT_DEFAULT) {
    elem->layout = layout;
  }

  resetPendingElement(ctx);
  printElement(elem, 0);
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

  ctx->pending->children = kids;
  ctx->pending->childCount = count;
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
  ctx->pending->name = n;
  return 0;
}

uint8_t width(Context *ctx, unsigned int w) {
  // printf("width: %d\n", w);
  ctx->pending->width = w;
  return 0;
}

uint8_t height(Context *ctx, unsigned int h) {
  // printf("height: %d\n", h);
  ctx->pending->height = h;
  return 0;
}

void begin(Context *ctx) {
  resetPendingElement(ctx);
}

void end(Context *ctx) {
  resetPendingElement(ctx);
}
