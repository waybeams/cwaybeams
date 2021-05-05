#include "beam_test.h"
#include "hash_test.h"
#include "hfsm_test.h"
#include "minunit.h"
#include "node_test.h"
#include "node_visitor_test.h"

char *allTests(void) {
  // Begin the test suite
  muSuiteStart();

  // box_test.h
  muRunTest(test_new_name_attr);
  muRunTest(test_new_height);
  muRunTest(test_new_width);
  muRunTest(test_new_larger_width);
  muRunTest(test_new_box);
  muRunTest(test_new_box_with_name);
  muRunTest(test_get_name);
  muRunTest(test_layout);
  muRunTest(test_default_layout);
  muRunTest(test_default_attr_values);
  muRunTest(test_configured_attr_values);
  muRunTest(test_attr_collection);
  muRunTest(test_node_types);
  muRunTest(test_element_children);

  // hash_test.h
  muRunTest(test_new_hash);

  // hfsm_test.h
  muRunTest(test_hfsm_creation);
  muRunTest(test_default_signal);

  // node_test.h
  muRunTest(test_new_char_attr);
  muRunTest(test_new_uint_attr);
  muRunTest(test_new_children);
  muRunTest(test_element_with_child);
  muRunTest(test_is_root);
  muRunTest(test_pointer_attr);
  printf("SKIPPED: test_leaf_hash\n");
  // muRunTest(test_leaf_hash);

  // node_visitor_test.h
  muRunTest(testDepthFirst);
  muRunTest(testBreadthFirst);
  muRunTest(testFindElementWithMatchingAttr);
  printf("SKIPPED: test_str_one\n");
  // muRunTest(test_str_one);
  printf("SKIPPED: test_str_kids\n");
  // muRunTest(test_str_kids);

  return NULL;
}

RUN_TESTS(allTests);