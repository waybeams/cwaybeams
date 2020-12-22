#include "minunit.h"
#include <dom.h>
#include <stdbool.h>
#include <stdlib.h>

char *testNewHeight(void) {
  Attr *one = height(23);
  unsigned int data = uintAttr(one);
  muAssert(data == 23, "Expected data to be 20");
  freeAttr(one);
  return NULL;
}

char *testNewWidth(void) {
  Attr *one = width(20);
  unsigned int data = uintAttr(one);
  muAssert(data == 20, "Expected data to be 20");
  freeAttr(one);
  return NULL;
}

char *testNewName(void) {
  Attr *one = name("kanachan");
  char *data = charAttr(one);
  muAssert(data == "kanachan", "Expected chars");
  freeAttr(one);
  return NULL;
}

char *testNewElement(void) {
  Element *one = box(width(20));
  muAssert(one->parentId == 0, "Expected empty parentId");
  freeElement(one);
  return NULL;
}
