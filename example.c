#include <stdio.h>
#include "dom.h"

Element* render(Context *c, char *title) {
  return vbox(c,
    name(c, title),
    width(c, 800),
    height(c, 600),
    children(c, 6,
      hbox(c, name(c, "hboxa")),
      hbox(c, name(c, "hboxb")),
      hbox(c,
        name(c, "hboxc"),
        children(c, 1,
          hbox(c, name(c, "deeper"))
        )
      ),
      hbox(c, name(c, "hboxd")),
      hbox(c, name(c, "hboxe")),
      vbox(c, name(c, "vboxb"))
    )
  );
}

int main(void) {
  printf("HELLO WORLD\n");
  Context c = {0};
  begin(&c);
  Element *root = render(&c, "Main Title");
  end(&c);

  printf("+++++++++++++++++++++++++++\n");
  printElement(root, 0);

  /*
  printElement(c.elements[0]);
  printElement(c.elements[1]);
  printElement(c.elements[2]);
  printElement(c.elements[3]);
  printElement(c.elements[4]);
  printElement(c.elements[5]);
  printElement(c.elements[6]);
  */

  return 0;
}
