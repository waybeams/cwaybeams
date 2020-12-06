#include "dom.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static ElementId lastId = 1;

void printElement(Element *elem) {
  printf("-----------------\n");
  printf("id: %d\n", elem->id);
  printf("parentId: %d\n", elem->parentId);
  printf("name: %s\n", elem->name);
  printf("layout: %d\n", elem->layout);
  printf("width: %d\n", elem->width);
  printf("height: %d\n", elem->height);

  // int count = sizeof(elem->children);
  // printf("elem size: %d", sizeof(elem->children[0]));
  // printf("child count: %d", count);
  // for (int i = 0; i < count; i++) {
    // printf("child[%d]: %d", i, elem->children[i]);
  // }
}

Element nextElement(Context *ctx) {
  Element elem = ctx->nextElement;
  // if (elem.id == 0) {
    // elem.id = 1;
  // }
  return elem;
}

unsigned int container(Context *ctx, Layout layout) {
  Element elem = nextElement(ctx);
  elem.layout = layout;
  ctx->elements[ctx->lastElementIndex++] = elem;

  Element nextElem = { .id = lastId += 1 };

  ctx->nextElement = nextElem;
  return elem.id;
}

unsigned int vbox(Context *ctx, ...) {
  return container(ctx, LAYOUT_VERTICAL);
}

unsigned int hbox(Context *ctx, ...) {
  return container(ctx, LAYOUT_HORIZONTAL);
}

unsigned int box(Context *ctx, ...) {
  return container(ctx, LAYOUT_STACK);
}

uint8_t name(Context *ctx, char *n) {
  printf("%s\n", n);
  ctx->nextElement.name = n;
  return 0;
}

uint8_t width(Context *ctx, unsigned int w) {
  printf("width: %d\n", w);
  ctx->nextElement.width = w;
  return 0;
}

uint8_t height(Context *ctx, unsigned int h) {
  printf("height: %d\n", h);
  ctx->nextElement.height = h;
  return 0;
}

uint8_t children(Context *ctx, unsigned int count, ...) {
  va_list kids;

  Element parent = ctx->nextElement;
  unsigned int *children;
  children = malloc(count * sizeof(ElementId));
  printf("children size %d\n", count);
  parent.children = children;

  va_start(kids, count);
  unsigned int kid_id;
  for (int i = 0; i < count; i++) {
    kid_id = va_arg(kids, unsigned int);
    if (kid_id != 0) {
      // printf("kid: %d\n", kid_id);
      ctx->elements[kid_id].parentId = parent.id;
      parent.children[i] = kid_id;
    }
  }

  va_end(kids);
  return 0;
}
