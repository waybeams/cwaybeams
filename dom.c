#include "dom.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static ElementId lastId = 1;

static Element *pendingElement;

void resetPendingElement() {
  free(pendingElement);
  pendingElement = malloc(sizeof(Element));
}

void copyElement(Element *source, Element *target) {
  target->id = source->id;
  target->height = source->height;
  target->name = source->name;
  target->width = source->width;
  // target->childIds = source->childIds;
  target->childCount = source->childCount;
  target->children = source->children;
}

void printElement(Element *elem) {
  printf("id: %d\n", elem->id);
  printf("parentId: %d\n", elem->parentId);
  printf("name: %s\n", elem->name);
  printf("layout: %d\n", elem->layout);
  printf("width: %d\n", elem->width);
  printf("height: %d\n", elem->height);
  printf("childCount: %d\n", elem->childCount);

  // for (int i = 0; i < elem->childCount; i++) {
    // Element *child = &elem->children[i];
    // printf(" >> childId[%d]: %d\n", i, child->id);
  // }

  printf("-----------------\n");
}

Element* container(Context *ctx, Layout layout) {
  Element *elem;
  elem = malloc(sizeof(Element));
  copyElement(pendingElement, elem);

  elem->id = lastId++;
  if (elem->layout == LAYOUT_DEFAULT) {
    elem->layout = layout;
  }
  resetPendingElement();

  /*
  if (ctx->pendingChildCount > 0) {
    //printf(">> Assigning %d childIds to id %d\n",
        //ctx->pendingChildCount, elem.id);
    elem->childIds = ctx->pendingChildIds;
    elem->childCount = ctx->pendingChildCount;
    ctx->pendingChildCount = 0;
    ctx->pendingChildIds = NULL;
  }
  */

  // printf("container for %d %s\n", elem.id, elem.name);
  printElement(elem);

  // ctx->elements[elem->id] = elem;
  // Element nextElem = {};
  // ctx->nextElement = nextElem;
  return elem;
}

uint8_t children(Context *ctx, unsigned int count, ...) {
  va_list kids;
  // Element parent = ctx->nextElement;
  // int elemSize = sizeof(ElementId);
  // printf("ELEM SIZE %d\n", elemSize);

  ElementId *childIds;
  childIds = malloc(count * sizeof(ElementId));
  printf("children count %d\n", count);
  // parent.childIds = childIds;

  Element children[count];
  // children = malloc(count * sizeof(Element*));

  va_start(kids, count);
  // unsigned int childId;
  Element *child;
  for (int i = 0; i < count; i++) {
    child = va_arg(kids, Element*);
    printf("CHILD ID: %d\n", child->id);
    children[i] = *child;
    // if (child != NULL) {
      // childIds[i] = child->id
      // printf("kid: %d\n", childId);
      // ctx->elements[childId].parentId = parent.id;
      // ctx->elements[childId].childCount = count;
    // }
  }

  va_end(kids);

  pendingElement->children = children;
  pendingElement->childIds = childIds;
  pendingElement->childCount = count;

  // ctx->pendingChildIds = childIds;
  // ctx->pendingChildCount = count;
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
  // ctx->nextElement.name = n;
  return 0;
}

uint8_t width(Context *ctx, unsigned int w) {
  // printf("width: %d\n", w);
  pendingElement->width = w;
  // ctx->nextElement.width = w;
  return 0;
}

uint8_t height(Context *ctx, unsigned int h) {
  // printf("height: %d\n", h);
  pendingElement->height = h;
  // ctx->nextElement.height = h;
  return 0;
}

void begin(Context *ctx) {
  resetPendingElement();
}

void end(Context *ctx) {
  // resetPendingElement();
}
