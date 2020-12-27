#include "minunit.h"
#include <dom.h>
#include <layout.h>
#include <stddef.h>

char *testNewLayout(void) {
  Element *root = box(name("root"));
  LayoutStatus s = layoutElement(root);
  muAssert(s == LayoutSuccess, "Expected layout success");
  freeElement(root);
  return NULL;
}

