#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

Element* render(Context *c, char *title) {
  return vbox(c,
    name(c, title),
    width(c, 800),
    height(c, 600),
    children(c, 6,
      hbox(c, name(c, "hboxa")),
      hbox(c, name(c, "hboxb")),
      hbox(c,
        name(c, "hboxc"),
        children(c, 1,
          hbox(c, name(c, "deeper"))
        )
      ),
      hbox(c, name(c, "hboxd")),
      hbox(c, name(c, "hboxe")),
      vbox(c, name(c, "vboxb"))
    )
  );
}

int exec(Context *c) {
  struct timeval st, et;
  gettimeofday(&st, NULL);
  render(c, "Main Title");
  gettimeofday(&et, NULL);
  int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Creation Time: %d micro seconds\n", elapsed);
  return elapsed;
}

int main(void) {
  int count = 100;
  // int durations[count];
  int duration;
  int sum = 0;
  Context c = {0};
  begin(&c);
  for (int i = 0; i < count; i++) {
    duration = exec(&c);
    // durations[i] = duration;
    sum += duration;
  }
  end(&c);

  printf("Average %d\n", sum / count);

  // printElement(root, 0);
  /*
  printElement(c.elements[0]);
  printElement(c.elements[1]);
  printElement(c.elements[2]);
  printElement(c.elements[3]);
  printElement(c.elements[4]);
  printElement(c.elements[5]);
  printElement(c.elements[6]);
  */

  return 0;
}
