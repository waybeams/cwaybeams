#include <stdio.h>
#include "dom.h"

uint8_t render_box(Context *ctx, char *title) {
  box(ctx,
    name(title),
    width(800),
    height(600),
    children(ctx,
      box(ctx, name("box1")),
      box(ctx, name("box2"))
    )
  );
  return 0;
}

int main(void) {
  printf("HELLO WORLD\n");
  Context *ctx;
  render_box(ctx, "Main Title");
  return 0;
}
