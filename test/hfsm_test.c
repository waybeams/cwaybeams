#include "fixtures/hfsm_keyboard.h"
#include "hfsm.h"
#include "hfsm_test.h"
#include "minunit.h"
#include "node.h"
#include <stdbool.h>

char *test_hfsm_creation(void) {
  Node *machine = new_hfsm_keyboard();
  char *name = hfsm_get_state_name(machine);
  muAssert(strcmp(name, "kb_no_caps") == 0, "Expected default state");

  free_node(machine);
  return NULL;
}

char *test_default_signal(void) {
  Node *machine = new_hfsm_keyboard();
  // TOOD(lbayes): Move to a separate test method
  // Node *state = hfsm_get_state(machine);
  // muAssert(state != NULL, "Expected valid state");

  char buf[2] = {0, 0};
  char *result = malloc(6 * sizeof(char));
  int index = 0;
  kb_send_signal(machine, (char *)buf, "a");
  result[index++] = buf[0];
  kb_send_signal(machine, (char *)buf, "b");
  result[index++] = buf[0];
  kb_send_signal(machine, buf, "c");
  result[index++] = buf[0];
  kb_send_signal(machine, buf, "d");
  result[index++] = buf[0];

  // Insert ending char.
  result[index++] = 0;
  muAssert(strcmp(result, "abcd") == 0, "Expected buffer to fill");

  free_node(machine);
  free(result);
  return NULL;
}

