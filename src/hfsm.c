#include "hfsm.h"
#include "node_visitor.h"
#include <stddef.h>

int hfsm_set_state(Node *machine, char *state_name) {
  return 0;
}

Node *hfsm_get_state(Node *machine) {
  char *name = hfsm_get_state_name(machine);
  return find_element_with_matching_char_attr(machine, HfsmAttrKeyName, name);
}
