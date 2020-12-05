#include <stdio.h>
#include "dom.h"

uint8_t render(Context *c, char *title) {
  return vbox(c,
    name(c, title),
    width(c, 800),
    height(c, 600),
    children(c,
      hbox(c, name(c, "hboxa")),
      vbox(c, name(c, "vboxb"))
    )
  );
}

int main(void) {
  printf("HELLO WORLD\n");
  Context c = {0};
  render(&c, "Main Title");

  printElement(&c.elements[0]);
  printElement(&c.elements[1]);
  printElement(&c.elements[2]);
  return 0;
}
