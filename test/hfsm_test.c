#include "hfsm_test.h"
#include "fixtures/hfsm_keyboard.h"
#include <minunit.h>
#include <stdbool.h>

char *test_hfsm_creation(void) {
  Element *machine = new_hfsm_keyboard();
  muAssert(machine != NULL, "Expected non-null machine");

  freeElement(machine);
  return NULL;
}
