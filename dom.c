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
  printf("childCount: %d\n", elem->childCount);

  for (int i = 0; i < elem->childCount; i++) {
    printf(" >> child[%d]: %d\n", i, elem->childIds[i]);
  }
}

unsigned int container(Context *ctx, Layout layout) {
  Element elem = ctx->nextElement;
  elem.id = lastId++;
  elem.layout = layout;
  if (ctx->pendingChildCount > 0) {
    //printf(">> Assigning %d childIds to id %d\n",
        //ctx->pendingChildCount, elem.id);
    elem.childIds = ctx->pendingChildIds;
    elem.childCount = ctx->pendingChildCount;
    ctx->pendingChildCount = 0;
    ctx->pendingChildIds = NULL;
  }

  // printf("container for %d %s\n", elem.id, elem.name);
  printElement(&elem);

  ctx->elements[elem.id] = elem;

  Element nextElem = {};
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
  printf("name: %s\n", n);
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

  // Element parent = ctx->nextElement;
  // int elemSize = sizeof(ElementId);
  // printf("ELEM SIZE %d\n", elemSize);

  ElementId *childIds;
  childIds = malloc(count * sizeof(ElementId));
  printf("childIds size %d\n", count);
  // parent.childIds = childIds;

  va_start(kids, count);
  unsigned int childId;
  for (int i = 0; i < count; i++) {
    childId = va_arg(kids, unsigned int);
    if (childId != 0) {
      childIds[i] = childId;
      // printf("kid: %d\n", childId);
      // ctx->elements[childId].parentId = parent.id;
      // ctx->elements[childId].childCount = count;
    }
  }

  va_end(kids);

  ctx->pendingChildIds = childIds;
  ctx->pendingChildCount = count;
  return 0;
}

void begin(Context *ctx) {
}

void end(Context *ctx) {
}
