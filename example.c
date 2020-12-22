#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* uiTree(char *title) {
  return box(
    name(title),
    width(800),
    height(600)
  );
}

int main(void) {
  Element *root = uiTree("root-node");
  printElement(root);
  freeElement(root);
  return 0;
}
