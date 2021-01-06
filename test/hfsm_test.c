#include "hfsm_test.h"
#include "fixtures/hfsm_keyboard.h"
#include <hfsm.h>
#include <minunit.h>
#include <stdbool.h>

char *test_hfsm_creation(void) {
  Element *machine = new_hfsm_keyboard();
  char *state = hfsm_get_state(machine);
  muAssert(strcmp(state, "kb_no_caps") == 0, "Expected default state");
  freeElement(machine);
  return NULL;
}

