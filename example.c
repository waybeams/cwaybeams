#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* customRender(char *title) {
  return newElement(3,
    name(title),
    width(800),
    height(600),
    children(1,
      newElement(1, name("child-1"))
    )
  );

  /*
  return vbox(
    name(title),
    width(800),
    height(600),
    children(6,
      hbox(name("hboxa")),
      hbox(c, name(c, "hboxb")),
      hbox(c,
        name(c, "hboxc"),
        children(c, 1,
          hbox(c, name(c, "deeper"))
        )
      ),
      vbox(name("vboxb"))
    )
  );
  */
}

int main(void) {
  Element *root = customRender("ROOT ELEMENT");
  printElement(root);
  freeElement(root);

  return 0;
}
