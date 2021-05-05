#include "hfsm_keyboard.h"
#include "hfsm.h"
#include <stddef.h>
#include <string.h>

int kb_caps_signal(char *buf, char *signal) {
  return 0;
}

int kb_no_caps_signal(char *buf, char *signal) {
  strcpy(buf, signal);
  // buf[0] = signal[0];
  return 0;
}

Node *new_hfsm_keyboard(void) {
  return hfsm_container(
    hfsm_name("kb_root"),
    hfsm_default_state_name("kb_no_caps"),
    // kb_signal_handler(kb_no_caps_signal),
    hfsm_children(
      hfsm_container(
        hfsm_name("kb_caps"),
        kb_signal_handler(kb_caps_signal)
      ),
      hfsm_container(
        hfsm_name("kb_no_caps"),
        kb_signal_handler(kb_no_caps_signal)
      )
    )
  );
}

Attr *kb_signal_handler(SignalHandler handler) {
  return new_ext_ptr_attr(KeyboardAttrSignal, (unsigned char *)handler);
}

SignalHandler *kb_get_signal_handler(Node *machine) {
  Node *state = hfsm_get_state(machine);
  SignalHandler *handler = (SignalHandler *)get_raw_attr_from_node(state, KeyboardAttrSignal);
  return handler;
}

int kb_send_signal(Node *machine, char *buf, char *signal) {
  SignalHandler *handler = kb_get_signal_handler(machine);
  if (handler == NULL) {
    return -1;
  }
  return handler(buf, signal);
}
