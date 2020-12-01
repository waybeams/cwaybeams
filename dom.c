#include "dom.h"
#include <stdarg.h>

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
  printf("box\n");
  return 0;
}

uint8_t children(Context *ctx, ...) {
  printf("children\n");
  return 0;
}
