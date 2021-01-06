#include "hfsm_test.h"
#include "fixtures/hfsm_keyboard.h"
#include <hfsm.h>
#include <minunit.h>
#include <stdbool.h>

char *test_hfsm_creation(void) {
  Node *machine = new_hfsm_keyboard();
  char *name = hfsm_get_state_name(machine);
  muAssert(strcmp(name, "kb_no_caps") == 0, "Expected default state");
  freeNode(machine);
  return NULL;
}

