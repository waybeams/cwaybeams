#include "dom.h"
#include <stdarg.h>

static int nextId(void) {
  return lastId++;
}

uint8_t name(char *n) {
  printf("%s\n", n);
  return 0;
}

uint8_t width(int w) {
  printf("width: %d\n", w);
  return 0;
}

uint8_t height(int h) {
  printf("height: %d\n", h);
  return 0;
}

uint8_t box(Context *ctx, ...) {
  int id = nextId();
  printf("box id:%d defined\n", id);
  return 0;
}

uint8_t children(Context *ctx, ...) {
  printf("children\n");
  return 0;
}
