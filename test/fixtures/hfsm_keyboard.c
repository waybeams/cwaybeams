#include "hfsm_keyboard.h"
#include "hfsm.h"
#include <stddef.h>
#include <stdio.h>

int kb_main_signal(int signal) {
  printf("Main Signal Handler: %d\n", signal);
  return 0;
}

int kb_caps_signal(int signal) {
  printf("Caps Signal Handler: %d\n", signal);
  return 0;
}

int kb_no_caps_signal(int signal) {
  printf("NO Caps Signal Handler: %d\n", signal);
  return 0;
}

Node *new_hfsm_keyboard(void) {
  return hfsm_container(
    hfsm_name("kb_root"),
    hfsm_default_state_name("kb_no_caps"),
    hfsm_children(
      hfsm_container(
        hfsm_name("kb_caps"),
        signal_handler(&kb_caps_signal)
      ),
      hfsm_container(
        hfsm_name("kb_no_caps"),
        signal_handler(kb_no_caps_signal)
      )
    )
  );
}

Attr *signal_handler(SignalHandler handler) {
  return new_ptr_attr(AttrTypeSignal, (unsigned char *)handler);
}

