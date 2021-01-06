#include "dom_visitor_test.h"
#include "minunit.h"
#include <dom_visitor.h>

Node *visited[13];
int visitedIndex = 0;

VisitStatus node_handler(Node *node) {
  visited[visitedIndex++] = node;
  return VISIT_SUCCESS;
}

static Node *create_tree(void) {
  visitedIndex = 0;

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

char *testFindElementWithMatchingAttr(void) {
  Node *root = create_tree();
  Node *missing = find_element_with_matching_char_attr(root, NameAttr,
      "not-in-tree");
  muAssert(missing == NULL, "Expected not found");
  Node *body = find_element_with_matching_char_attr(root, NameAttr, "body");
  muAssert(body != NULL, "Expected to find body");
  Node *title = find_element_with_matching_char_attr(root, NameAttr, "title");
  muAssert(title != NULL, "Expected to find title");
  muAssert(title->parent_id == body->id, "Expected child/parent relationship");
  freeNode(root);
  return NULL;
}

char *testBreadthFirst(void) {
  Node *root = create_tree();
  breadth_first(root, node_handler);

  muAssert(visitedIndex == 13, "Expected count");
  muAssert(strcmp(getName(visited[0]), "root") == 0, "root");
  muAssert(strcmp(getName(visited[1]), "head") == 0, "head");
  muAssert(strcmp(getName(visited[2]), "logo") == 0, "logo");
  muAssert(strcmp(getName(visited[3]), "page-title") == 0, "page-title");
  muAssert(strcmp(getName(visited[4]), "account") == 0, "account");
  muAssert(strcmp(getName(visited[5]), "body") == 0, "body");
  muAssert(strcmp(getName(visited[6]), "title") == 0, "title");
  muAssert(strcmp(getName(visited[7]), "content") == 0, "content");
  muAssert(strcmp(getName(visited[8]), "footer") == 0, "footer");
  muAssert(strcmp(getName(visited[9]), "foot") == 0, "foot");
  muAssert(strcmp(getName(visited[10]), "contact") == 0, "contact");
  muAssert(strcmp(getName(visited[11]), "about") == 0, "about");
  muAssert(strcmp(getName(visited[12]), "press") == 0, "press");

  freeNode(root);
  return NULL;
}

char *testDepthFirst(void) {
  Node *root = create_tree();
  depth_first(root, node_handler);

  muAssert(visitedIndex == 13, "Expected count");
  muAssert(strcmp(getName(visited[0]), "logo") == 0, "logo");
  muAssert(strcmp(getName(visited[1]), "page-title") == 0, "page-title");
  muAssert(strcmp(getName(visited[2]), "account") == 0, "account");
  muAssert(strcmp(getName(visited[3]), "head") == 0, "head");
  muAssert(strcmp(getName(visited[4]), "title") == 0, "title");
  muAssert(strcmp(getName(visited[5]), "content") == 0, "content");
  muAssert(strcmp(getName(visited[6]), "footer") == 0, "footer");
  muAssert(strcmp(getName(visited[7]), "body") == 0, "body");
  muAssert(strcmp(getName(visited[8]), "contact") == 0, "contact");
  muAssert(strcmp(getName(visited[9]), "about") == 0, "about");
  muAssert(strcmp(getName(visited[10]), "press") == 0, "press");
  muAssert(strcmp(getName(visited[11]), "foot") == 0, "foot");
  muAssert(strcmp(getName(visited[12]), "root") == 0, "root");

  freeNode(root);
  return NULL;
}

