#include "hfsm.h"
#include <stddef.h>
#include <dom_visitor.h>

int hfsm_signal(Node *machine, int signal) {
  return 0;
}

int hfsm_set_state(Node *machine, char *state_name) {
  return 0;
}

Node *hfsm_get_state(Node *machine) {
  char *name = hfsm_get_state_name(machine);

  return NULL;
}

