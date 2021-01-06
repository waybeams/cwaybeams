#include "minunit.h"
#include <dom.h>
#include <layout.h>
#include <stddef.h>

char *testNewLayout(void) {
  Node *root = box(name("root"));
  LayoutStatus s = layoutNode(root);
  muAssert(s == LayoutSuccess, "Expected layout success");
  freeNode(root);
  return NULL;
}

