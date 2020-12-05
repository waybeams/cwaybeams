#include "dom.h"
#include <stdarg.h>

static unsigned int incrId(void) {
  return lastId++;
}

static Element* getNextElement(Context *ctx) {
  if (ctx->nextElement == NULL) {
    printf("YOO NULL");
  }

  return ctx->nextElement;
}

Element* container(Context *ctx) {
  Element* elem = getNextElement(ctx);
  ctx->elements[ctx->lastIndex++] = elem;

  Element* nextElem;
  nextElem->id = incrId();
  ctx->nextElement = nextElem;
  return elem;
}

uint8_t name(char *n) {
  printf("%s\n", n);
  return 0;
}

uint8_t width(unsigned int w) {
  printf("width: %d\n", w);
  return 0;
}

uint8_t height(unsigned int h) {
  printf("height: %d\n", h);
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
