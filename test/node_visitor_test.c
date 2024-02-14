#include "arena.h"
#include "beam.h"
#include "minunit.h"
#include "node.h"
#include "node_visitor_test.h"
#include "test_helper.h"
#include <node_visitor.h>
#include <stdio.h>

typedef struct {
  node_t *nodes[20];
  s32_t visited_index;
}visited_context_t;

visit_status_t node_handler(node_t *node, void *userdata) {
  visited_context_t *c = userdata;
  c->nodes[c->visited_index] = node;
  c->visited_index++;
  return VISIT_SUCCESS;
}

static node_t *create_tree(void) {
  return vbox(
    name("root"),
    children(
      hbox(
        name("head"),
        children(
          box(name("logo")),
          box(name("page-title")),
          box(name("account"))
        )
      ),
      vbox(
        name("body"),
        children(
          box(name("title")),
          box(name("content")),
          box(name("footer"))
        )
      ),
      hbox(
        name("foot"),
        children(
          box(name("contact")),
          box(name("about")),
          box(name("press"))
        )
      )
    )
  );
}

char *test_find_element_with_matching_attr(void) {
  init_arena();
  node_t *root = create_tree();
  node_t *missing = find_element_with_matching_char_attr(root,
      BeamAttrKeysName, "not-in-tree", NULL);

  muAssert(missing == NULL, "Expected not found");
  node_t *body = find_element_with_matching_char_attr(root, BeamAttrKeysName,
      "body", NULL);
  muAssert(body != NULL, "Expected to find body");
  node_t *title = find_element_with_matching_char_attr(root, BeamAttrKeysName,
      "title", NULL);
  muAssert(title != NULL, "Expected to find title");
  muAssert(title->parent_id == body->id, "Expected child/parent relationship");

    arena_global_free();
  return NULL;
}

char *test_breadth_first(void) {
  init_arena();
  node_t *root = create_tree();
  visited_context_t *c = calloc(sizeof(visited_context_t), 1);
  breadth_first(root, node_handler, c);

  muAssertIntEq(c->visited_index, 13, "Expected count");
  muAssertStrEq(get_name(c->nodes[0]), "root", "root");
  muAssertStrEq(get_name(c->nodes[1]), "head", "head");
  muAssertStrEq(get_name(c->nodes[2]), "logo", "logo");
  muAssertStrEq(get_name(c->nodes[3]), "page-title", "page-title");
  muAssertStrEq(get_name(c->nodes[4]), "account", "account");
  muAssertStrEq(get_name(c->nodes[5]), "body", "body");
  muAssertStrEq(get_name(c->nodes[6]), "title", "title");
  muAssertStrEq(get_name(c->nodes[7]), "content", "content");
  muAssertStrEq(get_name(c->nodes[8]), "footer", "footer");
  muAssertStrEq(get_name(c->nodes[9]), "foot", "foot");
  muAssertStrEq(get_name(c->nodes[10]), "contact", "contact");
  muAssertStrEq(get_name(c->nodes[11]), "about", "about");
  muAssertStrEq(get_name(c->nodes[12]), "press", "press");

    arena_global_free();
  free(c);
  return NULL;
}

char *test_depth_first(void) {
  init_arena();
  node_t *root = create_tree();
  visited_context_t *c = calloc(sizeof(visited_context_t), 1);
  depth_first(root, node_handler, c);

  muAssertIntEq(c->visited_index, 13, "Expected count");
  muAssertStrEq(get_name(c->nodes[0]), "logo", "logo");
  muAssertStrEq(get_name(c->nodes[1]), "page-title", "page-title");
  muAssertStrEq(get_name(c->nodes[2]), "account", "account");
  muAssertStrEq(get_name(c->nodes[3]), "head", "head");
  muAssertStrEq(get_name(c->nodes[4]), "title", "title");
  muAssertStrEq(get_name(c->nodes[5]), "content", "content");
  muAssertStrEq(get_name(c->nodes[6]), "footer", "footer");
  muAssertStrEq(get_name(c->nodes[7]), "body", "body");
  muAssertStrEq(get_name(c->nodes[8]), "contact", "contact");
  muAssertStrEq(get_name(c->nodes[9]), "about", "about");
  muAssertStrEq(get_name(c->nodes[10]), "press", "press");
  muAssertStrEq(get_name(c->nodes[11]), "foot", "foot");
  muAssertStrEq(get_name(c->nodes[12]), "root", "root");

    arena_global_free();
  free(c);
  return NULL;
}
