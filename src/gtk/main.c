#include "box.h"
#include "render.h"

int new_app(int argc, char *argv[]) {
  Node *root = app(
    window(
      title("Main Example"),
      body(
        button(label("Jello")),
        button(label("Mello"))
      )
    )
  );

  return exec_app(root, argc, argv);
}
