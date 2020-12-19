#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;
static char *DEFAULT_NAME = "default";

static struct Element *newElement() {
  Element *elem = malloc(sizeof(Element));
  if (elem == NULL) {
    // malloc failed to get memory.
    return NULL;
  }

  elem->childCount = 0;
  elem->id = 0;
  elem->name = DEFAULT_NAME;
  elem->width = 0;
  elem->height = 0;
  elem->children = NULL;

  return elem;
}

void freeElement(struct Element *elem) {
  unsigned int count = elem->childCount;
  for (int i = 0; i < count; i++) {
    freeElement(&elem->children[i]);
  }
  free(elem);
}

/*
static void copyChildren(Element *target, Element *source) {
  unsigned int childCount = source->childCount;
  target->children = malloc(sizeof(Element) * childCount);
  if (target->children != NULL) {
    for (int i = 0; i < childCount; i++) {
      copyElement(&target->children[i], &source->children[i]);
    }
  }
}

static void copyElement(Element *target, Element *source) {
  target->id = source->id;
  target->height = source->height;
  target->width = source->width;
  target->childCount = source->childCount;
  target->children = NULL;

  strcpy(target->name, source->name);
  copyChildren(target, source);
}
*/

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
  // for (int i = 0; i < elem->childCount; i++) {
    // Element *child = &elem->children[i];
    // printf("%s>> child[%d].id: %d\n", tabs, i, child->id);
    // printElement(child, depth + 1);
  // }
  printf("%s-----------------\n", tabs);
}

Element *container(Context *ctx, Layout layout) {
  Element *elem = malloc(sizeof(Element));
  if (elem == NULL) {
    return NULL;
  }

  // copyElement(elem, ctx->pending);

  elem->id = lastId++;
  elem->layout = layout;

  ctx->pending = newElement();
  // printElement(elem, 0);
  // printf("elem %d\n", elem->id);
  return elem;
}

uint8_t children(Context *ctx, unsigned int count, ...) {
  va_list vargs;
  Element *kids = malloc(count * sizeof(Element));

  va_start(vargs, count);
  for (int i = 0; i < count; i++) {
    kids[i] = *va_arg(vargs, Element*);
  }

  va_end(vargs);

  ctx->pending->childCount = count;
  ctx->pending->children = kids;
  return 0;
}

Element* vbox(...) {
  return container(ctx, LAYOUT_VERTICAL);
}

Element* hbox(...) {
  return container(ctx, LAYOUT_HORIZONTAL);
}

Element* box(...) {
  return container(ctx, LAYOUT_STACK);
}

uint8_t name(char *n) {
  // printf("name: %s\n", n);
  ctx->pending->name = n;
  return 0;
}

uint8_t width(unsigned int w) {
  // printf("width: %d\n", w);
  ctx->pending->width = w;
  return 0;
}

uint8_t height(unsigned int h) {
  // printf("height: %d\n", h);
  ctx->pending->height = h;
  return 0;
}

void begin() {
  // ctx->pending = newElement();
}

void end() {
  // resetPendingElement(ctx);
}

