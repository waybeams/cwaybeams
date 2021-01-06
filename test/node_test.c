#include "minunit.h"
#include "node.h"
#include "dom.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *test_new_char_attr(void) {
  Attr *attr = new_char_attr(AttrTypeName, "abcd");
  char *data = get_char_attr_data(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  free_attr(attr);
  return NULL;
}

char *test_new_uint_attr(void) {
  Attr *attr = new_uint_attr(AttrTypeName, 1234);
  unsigned int data = get_uint_attr_data(attr);
  muAssert(data == 1234, "Expected 1234");
  free_attr(attr);
  return NULL;
}

char *test_new_children(void) {
  Node *root = vbox(name("root"));
  Attr *attr = new_children(1, root);

  struct Node **kids = get_nodes_attr(attr);
  char *name = get_name(kids[0]);
  muAssert(strcmp(name, "root") == 0, "Expected name root");
  free_attr(attr);
  return NULL;
}

char *test_element_with_child(void) {
  Node *root = box(
    name("root"),
    children(
      box(name("child-1"))
    )
  );

  free_node(root);
  return NULL;
}

char *test_is_root(void) {
  Node *root = box(
    name("root"),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      box(name("child-4"))
    )
  );

  muAssert(is_root(root), "Expected root");
  Node **kids = get_children(root);
  muAssert(!is_root(kids[0]), "Expected child to not be root");
  muAssert(!is_root(kids[1]), "Expected child to not be root");
  muAssert(!is_root(kids[2]), "Expected child to not be root");
  muAssert(!is_root(kids[3]), "Expected child to not be root");
  free_node(root);
  return NULL;
}

