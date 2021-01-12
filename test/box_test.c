#include "box.h"
#include "minunit.h"
#include "node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *test_new_name_attr(void) {
  Attr *attr = name("abcd");
  char *data = get_char_attr_data(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  free_attr(attr);
  return NULL;
}

char *test_new_height(void) {
  Attr *one = height(23);
  unsigned int data = get_uint_attr_data(one);
  muAssert(data == 23, "Expected data to be 23");
  free_attr(one);
  return NULL;
}

char *test_new_width(void) {
  Attr *one = width(20);
  unsigned int data = get_uint_attr_data(one);
  muAssert(data == 20, "Expected data to be 20");
  free_attr(one);
  return NULL;
}

char *test_new_larger_width(void) {
  Attr *attr = new_uint_attr(BoxAttrTypeWidth, 801);
  unsigned int value = get_uint_attr_data(attr);

  muAssert(value == 801, "Expected matching value");
  free_attr(attr);
  return NULL;
}

char *test_new_box(void) {
  Node *one = new_node(TypeNone, 0);
  muAssert(one->parent_id == 0, "Expected empty parent_id");
  free_node(one);
  return NULL;
}

char *test_new_box_with_name(void) {
  Node *one = box(name("abcd"));
  muAssert(one->parent_id == 0, "Expected empty parent_id");
  Attr *attr = one->attrs[0];
  char *name = get_char_attr_data(attr);
  muAssert(strcmp(name, "abcd") == 0, "Expected name attr");
  free_node(one);
  return NULL;
}

char *test_get_name(void) {
  Node *elem = box(name("root"));
  char *elemName = get_name(elem);
  muAssert(strcmp(elemName, "root") == 0, "Expected name root");
  free_node(elem);
  return NULL;
}

char *test_layout(void) {
  Node *root = vbox(name("root"));
  Layout layout = get_layout(root);
  muAssert(layout == LayoutVertical, "Expected VBox");
  free_node(root);
  return NULL;
}

char *test_default_layout(void) {
  Node *root = box(name("root"));
  Layout layout = get_layout(root);
  muAssert(layout == LayoutDefault, "Expected default layout");
  free_node(root);
  return NULL;
}

char *test_default_attr_values(void) {
  Node *root = box(name("root"));
  unsigned int w = get_width(root);
  unsigned int h = get_height(root);
  unsigned int x = get_x(root);
  unsigned int y = get_y(root);
  unsigned int z = get_z(root);

  muAssert(w == 0, "Expected width 0");
  muAssert(h == 0, "Expected height 0");
  muAssert(x == 0, "Expected x 0");
  muAssert(y == 0, "Expected y 0");
  muAssert(z == 0, "Expected z 0");

  free_node(root);
  return NULL;
}

char *test_configured_attr_values(void) {
  Node *root = box(
    name("root"),
    width(1001),
    height(2002),
    x(3003),
    y(4004),
    z(5005)
  );

  unsigned int w = get_width(root);
  unsigned int h = get_height(root);
  unsigned int x = get_x(root);
  unsigned int y = get_y(root);
  unsigned int z = get_z(root);

  muAssert(w == 1001, "Expected width 1001");
  muAssert(h == 2002, "Expected height 2002");
  muAssert(x == 3003, "Expected x 3003");
  muAssert(y == 4004, "Expected y 4004");
  muAssert(z == 5005, "Expected z 5005");

  free_node(root);
  return NULL;
}

char *test_attr_collection(void) {
  Node *root = vbox(name("root"), width(3000));
  char *n = get_name(root);
  muAssert(strcmp(n, "root") == 0, "Expected name");
  unsigned int w = get_width(root);
  muAssert(w == 3000, "Expected width");
  unsigned int h = get_height(root);
  muAssert(h == 0, "Expected default height");

  free_node(root);
  return NULL;
}

char *test_node_types(void) {
  Node *elem;

  elem = box(name("box"));
  muAssert(elem->type == TypeBox, "Expected Box");
  free_node(elem);

  elem = vbox(name("vbox"));
  muAssert(elem->type == TypeVBox, "Expected VBox");
  free_node(elem);

  elem = hbox(name("hbox"));
  muAssert(elem->type == TypeHBox, "Expected HBox");
  free_node(elem);
  return NULL;
}

char *test_element_children(void) {
  Node *root = vbox(children(
    box(name("one")),
    box(name("two")),
    box(name("three")),
    box(name("four"))
  ));

  muAssert(root->child_count == 4, "child count");
  struct Node **kids = get_children(root);
  muAssert(strcmp(get_name(kids[0]), "one") == 0, "one");
  muAssert(strcmp(get_name(kids[1]), "two") == 0, "two");
  muAssert(strcmp(get_name(kids[2]), "three") == 0, "three");
  muAssert(strcmp(get_name(kids[3]), "four") == 0, "four");
  free_node(root);
  return NULL;
}
