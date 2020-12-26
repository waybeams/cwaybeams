#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* uiControl(char *title) {
  return vbox(
    name(title),
    width(800),
    height(600),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      hbox(name("child-4"),
        children(
          box(name("child-4-1")),
          box(name("child-4-2")),
          box(name("child-4-3")),
          box(name("child-4-4")),
          box(name("child-4-5"))
        )
      ),
      box(name("child-5")),
      box(name("child-6")),
      box(name("child-7")),
      box(name("child-8"))
    )
  );
}

int main(void) {
  Element *root = uiControl("root-node");
  printElement(root);
  freeElement(root);
  return 0;
}
