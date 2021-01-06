#include "minunit.h"
#include <dom.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *testNewHeight(void) {
  Attr *one = height(23);
  unsigned int data = get_uint_attr_data(one);
  muAssert(data == 23, "Expected data to be 23");
  freeAttr(one);
  return NULL;
}

char *testNewWidth(void) {
  Attr *one = width(20);
  unsigned int data = get_uint_attr_data(one);
  muAssert(data == 20, "Expected data to be 20");
  freeAttr(one);
  return NULL;
}

char *testNewLargerWidth(void) {
  Attr *attr = new_uint_attr(WidthAttr, 801);
  unsigned int value = get_uint_attr_data(attr);

  muAssert(value == 801, "Expected matching value");
  freeAttr(attr);
  return NULL;
}

char *testNewNameAttr(void) {
  Attr *attr = name("abcd");
  char *data = get_char_attr_data(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  freeAttr(attr);
  return NULL;
}

char *testNewUintAttr(void) {
  Attr *attr = new_uint_attr(NameAttr, 1234);
  unsigned int data = get_uint_attr_data(attr);
  muAssert(data == 1234, "Expected 1234");
  freeAttr(attr);
  return NULL;
}

char *testNewCharAttr(void) {
  Attr *attr = new_char_attr(NameAttr, "abcd");
  char *data = get_char_attr_data(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  freeAttr(attr);
  return NULL;
}

char *testNewBox(void) {
  Node *one = new_node(TypeNone, 0);
  muAssert(one->parent_id == 0, "Expected empty parent_id");
  freeNode(one);
  return NULL;
}

char *testNewBoxWithName(void) {
  Node *one = box(name("abcd"));
  muAssert(one->parent_id == 0, "Expected empty parent_id");
  Attr *attr = one->attrs[0];
  char *name = get_char_attr_data(attr);
  muAssert(strcmp(name, "abcd") == 0, "Expected name attr");
  freeNode(one);
  return NULL;
}

char *testNewChildren(void) {
  Node *root = vbox(name("root"));
  Attr *attr = new_children(1, root);

  struct Node **kids = get_nodes_attr(attr);
  char *name = getName(kids[0]);
  muAssert(strcmp(name, "root") == 0, "Expected name root");
  freeAttr(attr);
  return NULL;
}

char *testElementWithChild(void) {
  Node *root = box(
    name("root"),
    children(
      box(name("child-1"))
    )
  );

  freeNode(root);
  return NULL;
}

char *testIsRoot(void) {
  Node *root = box(
    name("root"),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      box(name("child-4"))
    )
  );

  muAssert(isRoot(root), "Expected root");
  Node **kids = getChildren(root);
  muAssert(!isRoot(kids[0]), "Expected child to not be root");
  muAssert(!isRoot(kids[1]), "Expected child to not be root");
  muAssert(!isRoot(kids[2]), "Expected child to not be root");
  muAssert(!isRoot(kids[3]), "Expected child to not be root");
  freeNode(root);
  return NULL;
}

char *testGetName(void) {
  Node *elem = box(name("root"));
  char *elemName = getName(elem);
  muAssert(strcmp(elemName, "root") == 0, "Expected name root");
  freeNode(elem);
  return NULL;
}

char *testLayout(void) {
  Node *root = vbox(name("root"));
  Layout layout = getLayout(root);
  muAssert(layout == LayoutVertical, "Expected VBox");
  freeNode(root);
  return NULL;
}

char *testDefaultLayout(void) {
  Node *root = box(name("root"));
  Layout layout = getLayout(root);
  muAssert(layout == LayoutDefault, "Expected default layout");
  freeNode(root);
  return NULL;
}

char *testDefaultAttrValues(void) {
  Node *root = box(name("root"));
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

  freeNode(root);
  return NULL;
}

char *testConfiguredAttrValues(void) {
  Node *root = box(
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

  freeNode(root);
  return NULL;
}

bool fakeHandlerCalled = false;
void fakeHandler(void) {
  fakeHandlerCalled = true;
}

char *testHandler(void) {
  /*
   * TODO(lbayes): Figure out event handlers vs signals.
  fakeHandlerCalled = false;
  Node *root = vbox(eventHandler("onclick", fakeHandler));
  emitEvent(root, "onclick");
  muAssert(fakeHandlerCalled == true, "Expected fakeHandlerCalled");
  freeNode(root);
  */
  return NULL;
}

char *testAttrCollection(void) {
  Node *root = vbox(name("root"), width(3000));
  char *n = getName(root);
  muAssert(strcmp(n, "root") == 0, "Expected name");
  unsigned int w = getWidth(root);
  muAssert(w == 3000, "Expected width");
  unsigned int h = getHeight(root);
  muAssert(h == 0, "Expected default height");

  freeNode(root);
  return NULL;
}

char *testNodeTypes(void) {
  Node *elem;

  elem = box(name("box"));
  muAssert(elem->type == TypeBox, "Expected Box");
  freeNode(elem);

  elem = vbox(name("vbox"));
  muAssert(elem->type == TypeVBox, "Expected VBox");
  freeNode(elem);

  elem = hbox(name("hbox"));
  muAssert(elem->type == TypeHBox, "Expected HBox");
  freeNode(elem);
  return NULL;
}

char *testElementChildren(void) {
  Node *root = vbox(children(
    box(name("one")),
    box(name("two")),
    box(name("three")),
    box(name("four"))
  ));

  muAssert(root->child_count == 4, "child count");

  struct Node **kids = getChildren(root);
  muAssert(strcmp(getName(kids[0]), "one"), "one");
  muAssert(strcmp(getName(kids[1]), "two"), "two");
  muAssert(strcmp(getName(kids[2]), "three"), "three");
  muAssert(strcmp(getName(kids[3]), "four"), "four");
  freeNode(root);
  return NULL;
}
