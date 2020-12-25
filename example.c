#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* uiControl(char *title) {
  return box(
    name(title),
    width(800),
    height(600),
    children(
      box(name("child-1")),
      box(
        name("child-4-container"),
        children(
          box(name("child-5")),
          box(name("child-6")),
          box(name("child-7")),
          box(name("child-8")),
          box(name("child-9"))
        )
      ),
      box(name("child-10")),
      box(name("child-11")),
      box(name("child-12"))
    )
  );
}

int main(void) {
  Element *root = uiControl("root-node");
  printElement(root);
  freeElement(root);
  return 0;
}
