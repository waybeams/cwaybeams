#include "hfsm_keyboard.h"
#include <hfsm.h>
#include <stddef.h>
#include <stdio.h>

void kb_shift_up_signal(void) {
  printf("YOOOOOOOOOOO\n");
}

Element *new_hfsm_keyboard(void) {
  return hfsm_state(
    hfsm_name("kb_root"),
    hfsm_children(
      hfsm_state(
        hfsm_name("kb_shift_up"),
        hfsm_signal_handler(kb_shift_up_signal)
      ),
      hfsm_state(
        hfsm_name("kb_shift_down")
      )
    )
  );
}

