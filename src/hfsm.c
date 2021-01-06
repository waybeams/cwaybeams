#include "hfsm.h"
#include <stddef.h>

int hfsm_signal(Element *machine, int signal) {
  return 0;
}

int hfsm_set_state(Element *machine, char *state_name) {
  return 0;
}

Element *hfsm_get_state(Element *machine) {
  char *name = hfsm_get_state_name(machine);

}

