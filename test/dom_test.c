#include "minunit.h"
#include <dom.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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
  Attr *one = name("abcd");
  char *data = charAttrData(one);
  muAssert(data == "abcd", "Expected abcd");
  freeAttr(one);
  return NULL;
}

char *testNewCharAttr(void) {
  Attr *attr = newCharAttr(Name, "abcd");
  char *data = charAttrData(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  freeAttr(attr);
  return NULL;
}

char *testNewElement(void) {
  Element *one = box(width(20));
  muAssert(one->parentId == 0, "Expected empty parentId");
  freeElement(one);
  return NULL;
}
