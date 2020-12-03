#include <stdio.h>
#include "dom.h"

uint8_t render(Context *ctx, char *title) {
  box(ctx,
    name(title),
    width(800),
    height(600),
    children(ctx,
      box(ctx, name("boxa")),
      box(ctx, name("boxb"))
    )
  );
  return 0;
}

int main(void) {
  printf("HELLO WORLD\n");
  Context *ctx;
  render(ctx, "Main Title");
  return 0;
}
