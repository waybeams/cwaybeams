#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* uiTree(char *title) {
  return box(
    name(title),
    width(800),
    height(600),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      box(name("child-4")),
      box(name("child-5")),
      box(name("child-6"))
    )
  );
}

int main(void) {
  Element *root = uiTree("root");
  printElement(root);
  freeElement(root);
  return 0;
}
