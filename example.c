#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* uiControl(char *title) {
  return box(
    name(title),
    width(800),
    height(600)
  );
}

int main(void) {
  Element *root = uiControl("root-node");
  printElement(root);
  freeElement(root);
  return 0;
}
