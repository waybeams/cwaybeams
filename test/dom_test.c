#include "minunit.h"
#include <dom.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *testNewHeight(void) {
  Attr *one = height(23);
  unsigned int data = getUintAttr(one);
  muAssert(data == 23, "Expected data to be 23");
  freeAttr(one);
  return NULL;
}

char *testNewWidth(void) {
  Attr *one = width(20);
  unsigned int data = getUintAttr(one);
  muAssert(data == 20, "Expected data to be 20");
  freeAttr(one);
  return NULL;
}

char *testNewLargerWidth(void) {
  Attr *attr = newUintAttr(WidthAttr, 801);
  unsigned int value = getUintAttr(attr);

  muAssert(value == 801, "Expected matching value");
  freeAttr(attr);
  return NULL;
}

char *testNewNameAttr(void) {
  Attr *attr = name("abcd");
  char *data = getCharAttr(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  freeAttr(attr);
  return NULL;
}

char *testNewUintAttr(void) {
  Attr *attr = newUintAttr(NameAttr, 1234);
  unsigned int data = getUintAttr(attr);
  muAssert(data == 1234, "Expected 1234");
  freeAttr(attr);
  return NULL;
}

char *testNewCharAttr(void) {
  Attr *attr = newCharAttr(NameAttr, "abcd");
  char *data = getCharAttr(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  freeAttr(attr);
  return NULL;
}

char *testNewBox(void) {
  Element *one = newElement(0);
  muAssert(one->parentId == 0, "Expected empty parentId");
  freeElement(one);
  return NULL;
}

char *testNewBoxWithName(void) {
  Element *one = newElement(1, name("abcd"));
  muAssert(one->parentId == 0, "Expected empty parentId");
  Attr *attr = one->attrs[0];
  char *name = getCharAttr(attr);
  muAssert(strcmp(name, "abcd") == 0, "Expected name attr");
  freeElement(one);
  return NULL;
}

char *testNewChildren(void) {
  Element *root = newElement(1, name("root"));
  Attr *attr = newChildren(1, root);

  struct Element **kids = getChildrenAttr(attr);
  char *name = getName(kids[0]);
  muAssert(strcmp(name, "root") == 0, "Expected name root");

  freeAttr(attr);
  return NULL;
}

char *testElementWithChild(void) {
  Element *root = box(
    name("root"),
    children(
      box(name("child-1"))
    )
  );

  freeElement(root);
  return NULL;
}

char *testElementSize(void) {
  Element *root = box(width(801), height(601));
  muAssert(root->width == 801, "Expected width assignment");
  muAssert(root->height == 601, "Expected height assignment");
  freeElement(root);
  return NULL;
}

char *testIsRoot(void) {
  Element *root = box(
    name("root"),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      box(name("child-4"))
    )
  );

  muAssert(isRoot(root), "Expected root");
  Element **kids = getChildren(root);
  muAssert(!isRoot(kids[0]), "Expected child to not be root");
  muAssert(!isRoot(kids[1]), "Expected child to not be root");
  muAssert(!isRoot(kids[2]), "Expected child to not be root");
  muAssert(!isRoot(kids[3]), "Expected child to not be root");
  freeElement(root);
  return NULL;
}

char *testGetName(void) {
  Element *root = box(name("root"));
  char *elemName = getName(root);
  muAssert(strcmp(elemName, "root") == 0, "Expected name root");
  freeElement(root);
  return NULL;
}

char *testDefaultLayout(void) {
  Element *root = box(name("root"));
  Layout layout = getLayout(root);
  muAssert(layout == LayoutDefault, "Expected default layout");
  freeElement(root);
  return NULL;
}

char *testLayout(void) {
  Element *root = vbox(name("root"));
  Layout layout = getLayout(root);
  muAssert(layout == LayoutVertical, "Expected VBox");
  freeElement(root);
  return NULL;
}

bool fakeHandlerCalled = false;
void fakeHandler(void) {
  fakeHandlerCalled = true;
}

char *testHandler(void) {
  fakeHandlerCalled = false;
  Element *root = vbox(handler("onclick", fakeHandler));
  emitEvent(root, "onclick");
  muAssert(fakeHandlerCalled == true, "Expected fakeHandlerCalled");
  freeElement(root);
  return NULL;
}

