#include "arena.h"
#include "beam.h"
#include "minunit.h"
#include "node.h"
#include "node_test.h"
#include "test_helper.h"
#include <string.h>

char *test_new_char_attr(void) {
  printf("SIZE?: %ld\n", sizeof(node_t));
  init_arena();
  attr_t *attr = new_char_attr(FakeNodeKeysName, "abcd");
  char *data = get_char_attr_data(attr);
  muAssertStrEq(data, "abcd", "Expected abcd");
    arena_global_free();
  return NULL;
}

char *test_new_uint_attr(void) {
  init_arena();
  attr_t *attr = new_u32_attr(FakeNodeKeysSize, 1234);
  u32_t data = get_u32_attr_data(attr);
  muAssertIntEq(data, 1234, "Expected 1234");
    arena_global_free();
  return NULL;
}

char *test_new_children(void) {
  init_arena();

  node_t *root = vbox(name("root"));
  attr_t *attr = new_children(1, root);

  struct node_t **kids = get_children_attr_data(attr);
  char *name = fake_get_name(kids[0]);
  muAssertStrEq(name, "root", "Expected name root");

    arena_global_free();
  return NULL;
}

char *test_element_with_child(void) {
  init_arena();

  node_t *root = box(
    name("root"),
    children(
      box(name("child-1"))
    )
  );
  muAssert(root != NULL, "Expected root node");

    arena_global_free();
  return NULL;
}

char *test_is_root(void) {
  init_arena();
  node_t *root = box(
    name("root"),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      box(name("child-4"))
    )
  );

  muAssert(is_root(root), "Expected root");
  node_t **kids = get_children(root);
  muAssert(!is_root(kids[0]), "Expected child to not be root");
  muAssert(!is_root(kids[1]), "Expected child to not be root");
  muAssert(!is_root(kids[2]), "Expected child to not be root");
  muAssert(!is_root(kids[3]), "Expected child to not be root");

    arena_global_free();
  return NULL;
}

/**
 * Function that is being used to test the pointer_attr creation
 * and retrieval.
 */
s32_t sum_func(s32_t a, s32_t b) {
  return a + b;
}

char *test_pointer_attr(void) {
  init_arena();
  attr_t *attr = new_ext_ptr_attr(FakeNodeKeysFunc, (unsigned char *)sum_func);
  FakeAddFunc *f = (FakeAddFunc *)get_attr_data(attr);
  // #include <inttypes.h>
  // printf("0x%" PRIXPTR "\n", (uintptr_t)f);
  s32_t result = f(2, 3);
  muAssertIntEq(result, 5, "Expected function to work");

    arena_global_free();
  return NULL;
}

char *test_leaf_hash(void) {
  init_arena();

  node_t *one = box(name("abcd"));
  node_t *two = box(name("abcd"));
  node_t *three = box(name("efgh"));

  muAssert(one->hash == two->hash, "Expected one and two");
  muAssert(one->hash != three->hash, "Expected one and three");
  muAssert(two->hash != three->hash, "Expected one and three");

    arena_global_free();
  return NULL;
}

// char *test_str_one(void) {
//   init_arena();
//   char result[256] = {0};
//   node_t *root = node(name("abcd"));
//   node_to_str(result, root);
//   char *expected = "\nnode.type=0 attr_104.type=2 attr_104.chars=abcd";
//   muAssertStrEq(result, expected, "Expect string match");
//
//   arena_global_free();
//   return NULL;
// }
//
// char *test_str_kids(void) {
//   node_t *root = node(
//     name("abcd"),
//     children(
//       node(name("efgh")),
//       node(name("ijkl"))
//     )
//   );
//
//   char result[256] = {0};
//   node_to_str(result, root);
//
//   char *expected = "\nnode.type=0 attr_104.type=2 attr_104.chars=abcd attr_1.type=1\n
// \tnode.type=0 attr_104.type=2 attr_104.chars=efgh\n
// \tnode.type=0 attr_104.type=2 attr_104.chars=ijkl";
//   muAssertStrEq(result, expected, "Expect string match");
//
//   arena_global_free();
//   return NULL;
// }
