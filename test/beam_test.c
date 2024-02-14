#include "arena.h"
#include "beam.h"
#include "minunit.h"
#include "node.h"
#include "test_helper.h"
#include <string.h>

char *test_new_name_attr(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  attr_t *attr = name("abcd");
  char *data = get_char_attr_data(attr);
  muAssertStrEq(data, "abcd", "Expected abcd");
  teardown_arena();
  return NULL;
}

char *test_new_height(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  attr_t *one = height(23);
  u32_t data = get_u32_attr_data(one);
  muAssertIntEq(data, 23, "Expected data to be 23");
  teardown_arena();
  return NULL;
}

char *test_new_width(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  attr_t *one = width(20);
  s32_t data = get_s32_attr_data(one);
  muAssertIntEq(data, 20, "Expected data to be 20");
  teardown_arena();
  return NULL;
}

char *test_new_larger_width(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  attr_t *attr = new_s32_attr(BeamAttrKeysWidth, 801);
  s32_t value = get_s32_attr_data(attr);

  muAssertIntEq(value, 801, "Expected matching value");
  teardown_arena();
  return NULL;
}

char *test_new_box(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *one = new_node(BeamTypeNone, 0);
  muAssert(one->parent_id == 0, "Expected empty parent_id");
  teardown_arena();
  return NULL;
}

char *test_new_box_with_name(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *one = box(name("abcd"));
  muAssert(one->parent_id == 0, "Expected empty parent_id");
  attr_t *attr = one->attrs[0];
  char *name = get_char_attr_data(attr);
  muAssertStrEq(name, "abcd", "Expected name attr");
  teardown_arena();
  return NULL;
}

char *test_get_name(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *elem = box(name("root"));
  char *elemName = get_name(elem);
  muAssertStrEq(elemName, "root", "Expected name root");
  teardown_arena();
  return NULL;
}

char *test_default_vbox_layout(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = vbox(name("root"));
  beam_layout_t layout = get_layout(root);
  muAssert(layout == LayoutVertical, "Expected VBox");
  teardown_arena();
  return NULL;
}

char *test_default_box_layout(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = box(name("root"));
  beam_layout_t layout = get_layout(root);
  muAssert(layout == LayoutDefault, "Expected default layout");
  teardown_arena();
  return NULL;
}

char *test_default_attr_values(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = box(name("root"));
  s32_t w = get_width(root);
  s32_t h = get_height(root);
  s32_t x = get_x(root);
  s32_t y = get_y(root);
  s32_t z = get_z(root);

  muAssertIntEq(w, 0, "Expected width 0");
  muAssertIntEq(h, 0, "Expected height 0");
  muAssertIntEq(x, 0, "Expected x 0");
  muAssertIntEq(y, 0, "Expected y 0");
  muAssertIntEq(z, 0, "Expected z 0");

  teardown_arena();
  return NULL;
}

char *test_configured_attr_values(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = box(
    name("root"),
    width(-1001),
    height(-2002),
    x(-3003),
    y(-4004),
    z(-5005)
  );

  s32_t w = get_width(root);
  s32_t h = get_height(root);
  s32_t x = get_x(root);
  s32_t y = get_y(root);
  s32_t z = get_z(root);

  muAssertIntEq(w, -1001, "Expected width 1001");
  muAssertIntEq(h, -2002, "Expected height 2002");
  muAssertIntEq(x, -3003, "Expected x 3003");
  muAssertIntEq(y, -4004, "Expected y 4004");
  muAssertIntEq(z, -5005, "Expected z 5005");

  teardown_arena();
  return NULL;
}

char *test_attr_collection(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = vbox(name("root"), width(3000));
  char *n = get_name(root);
  muAssertStrEq(n, "root", "Expected name");
  s32_t w = get_width(root);
  muAssert(w == 3000, "Expected width");
  s32_t h = get_height(root);
  muAssert(h == 0, "Expected default height");

  teardown_arena();
  return NULL;
}

char *test_node_types(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *elem;

  elem = box(name("box"));
  muAssert(elem->type == BeamTypeBox, "Expected Box");

  elem = vbox(name("vbox"));
  muAssert(elem->type == BeamTypeVBox, "Expected VBox");

  elem = hbox(name("hbox"));
  muAssert(elem->type == BeamTypeHBox, "Expected HBox");
  teardown_arena();
  return NULL;
}

char *test_element_children(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = vbox(children(
    box(name("one")),
    box(name("two")),
    box(name("three")),
    box(name("four"))
  ));

  muAssert(get_child_count(root) == 4, "child count");
  struct node_t **kids = get_children(root);
  muAssertStrEq(get_name(kids[0]), "one", "one");
  muAssertStrEq(get_name(kids[1]), "two", "two");
  muAssertStrEq(get_name(kids[2]), "three", "three");
  muAssertStrEq(get_name(kids[3]), "four", "four");

  teardown_arena();
  return NULL;
}

char *test_element_children_itr(void) {
  setup_arena(DEFAULT_ARENA_SIZE);
  node_t *root = vbox(children(
    box(name("one")),
    box(name("two")),
    box(
      name("three"),
      children(
        box(name("three-a")),
        box(name("three-b")),
        box(name("three-c"))
      )
    ),
    box(name("four"))
  ));

  s32_t child_count = get_child_count(root);
  muAssert(child_count == 4, "child count");

  struct node_t **kids = get_children(root);
  bool went_inside = false;
  for (s32_t i = 0; i < child_count; i++) {
    if (i == 2) {
      muAssert(get_child_count(kids[i]) == 3, "Expected grandchildren");

      struct node_t **g_kids = get_children(kids[i]);
      muAssertStrEq(get_name(g_kids[0]), "three-a", "aye");
      muAssertStrEq(get_name(g_kids[1]), "three-b", "aye");
      muAssertStrEq(get_name(g_kids[2]), "three-c", "aye");
      went_inside = true;
    }
  }

  muAssert(went_inside, "Expected loop inside");
  teardown_arena();
  return NULL;
}
