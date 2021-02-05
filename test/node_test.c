#include "box.h"
#include "minunit.h"
#include "node.h"
#include "node_test.h"
#include "str_builder.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *test_new_char_attr(void) {
  Attr *attr = new_char_attr(FakeNodeKeysName, "abcd");
  char *data = get_char_attr_data(attr);
  muAssert(strcmp(data, "abcd") == 0, "Expected abcd");
  free_attr(attr);
  return NULL;
}

char *test_new_uint_attr(void) {
  Attr *attr = new_uint_attr(FakeNodeKeysSize, 1234);
  unsigned int data = get_uint_attr_data(attr);
  muAssert(data == 1234, "Expected 1234");
  free_attr(attr);
  return NULL;
}

char *test_new_children(void) {
  Node *root = vbox(name("root"));
  Attr *attr = new_children(1, root);

  struct Node **kids = get_children_attr_data(attr);
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

/**
 * Function that is being used to test the pointer_attr creation
 * and retrieval.
 */
int add_func(int a, int b) {
  return a + b;
}

char *test_pointer_attr(void) {
  Attr *attr = new_ext_ptr_attr(FakeNodeKeysFunc, (unsigned char *)add_func);
  FakeAddFunc *f = (FakeAddFunc *)get_attr_data(attr);
  // #include <inttypes.h>
  // printf("0x%" PRIXPTR "\n", (uintptr_t)f);
  int result = f(2, 3);
  muAssert(result == 5, "Expected function to work");

  free_attr(attr);
  return NULL;
}

char *test_leaf_hash(void) {
  Node *one = box(name("abcd"));
  Node *two = box(name("abcd"));
  Node *three = box(name("efgh"));

  muAssert(one->hash == two->hash, "Expected one and two");
  muAssert(one->hash != three->hash, "Expected one and three");
  muAssert(two->hash != three->hash, "Expected one and three");

  free_node(one);
  free_node(two);
  free_node(three);
  return NULL;
}

char *test_str_one(void) {
  Node *root = node(name("abcd"));
  str_builder_t *str = node_to_str(root);
  char *result = str_builder_dump(str, NULL);
  char *expected = "\nnode.type=0 attr_104.type=2 attr_104.chars=abcd";
  muAssert(strcmp(result, expected) == 0, "Expect string match");

  str_builder_destroy(str);
  free(result);
  free_node(root);
  return NULL;
}

char *test_str_kids(void) {
  Node *root = node(
    name("abcd"),
    children(
      node(name("efgh")),
      node(name("ijkl"))
    )
  );

  str_builder_t *str = node_to_str(root);
  char *result = str_builder_dump(str, NULL);

  char *expected = "\nnode.type=0 attr_104.type=2 attr_104.chars=abcd attr_1.type=1\n\
\tnode.type=0 attr_104.type=2 attr_104.chars=efgh\n\
\tnode.type=0 attr_104.type=2 attr_104.chars=ijkl";
  muAssert(strcmp(result, expected) == 0, "Expect string match");
  // print_node(root);
  str_builder_destroy(str);
  free(result);
  free_node(root);
  return NULL;
}

