#include "minunit.h"
#include <dom.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
  Element *one = newElement(TypeNone, 0);
  muAssert(one->parentId == 0, "Expected empty parentId");
  muAssert(one->type == TypeNone, "Expected type");
  freeElement(one);
  return NULL;
}

char *testNewBoxWithName(void) {
  Element *one = newElement(TypeNone, 1, name("abcd"));
  muAssert(one->parentId == 0, "Expected empty parentId");
  Attr *attr = one->attrs[0];
  char *name = getCharAttr(attr);
  muAssert(strcmp(name, "abcd") == 0, "Expected name attr");
  muAssert(one->type == TypeNone, "Expected type");
  freeElement(one);
  return NULL;
}

char *testNewChildren(void) {
  Element *root = newElement(TypeNone, 1, name("root"));
  Attr *attr = newChildren(1, root);

  struct Element **kids = getElementsAttr(attr);
  char *name = getName(kids[0]);
  muAssert(strcmp(name, "root") == 0, "Expected name root");
  muAssert(root->type == TypeNone, "Expected type");

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

char *testLayout(void) {
  Element *root = vbox(name("root"));
  Layout layout = getLayout(root);
  muAssert(layout == LayoutVertical, "Expected VBox");
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

char *testDefaultAttrValues(void) {
  Element *root = box(name("root"));
  unsigned int w = getWidth(root);
  unsigned int h = getHeight(root);
  unsigned int x = getX(root);
  unsigned int y = getY(root);
  unsigned int z = getZ(root);

  muAssert(w == 0, "Expected width 0");
  muAssert(h == 0, "Expected height 0");
  muAssert(x == 0, "Expected x 0");
  muAssert(y == 0, "Expected y 0");
  muAssert(z == 0, "Expected z 0");

  freeElement(root);
  return NULL;
}

char *testConfiguredAttrValues(void) {
  Element *root = box(
    name("root"),
    width(1001),
    height(2002),
    x(3003),
    y(4004),
    z(5005)
  );

  unsigned int w = getWidth(root);
  unsigned int h = getHeight(root);
  unsigned int x = getX(root);
  unsigned int y = getY(root);
  unsigned int z = getZ(root);

  muAssert(w == 1001, "Expected width 1001");
  muAssert(h == 2002, "Expected height 2002");
  muAssert(x == 3003, "Expected x 3003");
  muAssert(y == 4004, "Expected y 4004");
  muAssert(z == 5005, "Expected z 5005");

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

char *testAttrCollection(void) {
  Element *root = vbox(name("root"), width(3000));
  char *n = getName(root);
  muAssert(strcmp(n, "root") == 0, "Expected name");
  unsigned int w = getWidth(root);
  muAssert(w == 3000, "Expected width");
  unsigned int h = getHeight(root);
  muAssert(h == 0, "Expected default height");

  freeElement(root);
  return NULL;
}

