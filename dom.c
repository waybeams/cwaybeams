#include "dom.h"
#include <stdarg.h>

static unsigned int lastId = 0;

static unsigned int incrId(void) {
  return lastId += 1;
}

void printElement(Element *elem) {
  printf("-----------------\n");
  printf("id: %d\n", elem->id);
  printf("name: %s\n", elem->name);
  printf("width: %d\n", elem->width);
  printf("height: %d\n", elem->height);
}

uint8_t container(Context *ctx) {
  Element elem = ctx->nextElement;
  ctx->elements[ctx->lastIndex++] = elem;

  Element nextElem = { .id = incrId() };

  ctx->nextElement = nextElem;
  return 0;
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

uint8_t box(Context *ctx, ...) {
  container(ctx);

  // printf("box id:%d created\n", elem->id);
  return 0;
}

uint8_t children(Context *ctx, ...) {
  printf("children\n");
  return 0;
}
