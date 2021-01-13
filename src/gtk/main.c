#include "box.h"
#include "render.h"
#include <stdlib.h>

static char *window_title = "Default Title";

Node *render_body(BoxServices s) {
  return body(
    button(label("Jello")),
    button(label("Mello"))
  );
}

Node *render_app(BoxServices s) {
  return app(
    window(
      title(window_title),
      body_renderer(render_body)
    )
  );
}

BoxServices *new_services(void) {
  BoxServices *s = malloc(sizeof(BoxServices));
  return s;
}

int main(int argc, char *argv[]) {
  window_title = "Updated Title";
  return render_app(new_services());
  // return exec_app(my_renderer, new_services());
}
