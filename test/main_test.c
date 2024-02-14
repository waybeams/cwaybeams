#include "arena_test.h"
#include "beam_test.h"
#include "hash_test.h"
#include "log.h"
#include "minunit.h"
#include "node_test.h"
#include "node_visitor_test.h"

char *allTests(void) {
  // Begin the test suite
  muSuiteStart();

  // arena_test.h
  muRunTest(test_arena_init);
  muRunTest(test_arena_malloc);
  muRunTest(test_arena_malloc_fail);
  muRunTest(test_arena_malloc_reset);
  muRunTest(test_arena_calloc);

  // beam_test.h
  muRunTest(test_new_name_attr);
  muRunTest(test_new_height);
  muRunTest(test_new_width);
  muRunTest(test_new_larger_width);
  muRunTest(test_new_box);
  muRunTest(test_new_box_with_name);
  muRunTest(test_get_name);
  muRunTest(test_default_vbox_layout);
  muRunTest(test_default_box_layout);
  muRunTest(test_default_attr_values);
  muRunTest(test_configured_attr_values);
  muRunTest(test_attr_collection);
  muRunTest(test_node_types);
  muRunTest(test_element_children);
  muRunTest(test_element_children_itr);

  // hash_test.h
  muRunTest(test_new_hash);

  // node_test.h
  muRunTest(test_new_char_attr);
  muRunTest(test_new_uint_attr);
  muRunTest(test_new_children);
  muRunTest(test_element_with_child);
  muRunTest(test_is_root);
  muRunTest(test_pointer_attr);
  log_info("SKIPPED: test_leaf_hash");
  // muRunTest(test_leaf_hash);

  // node_visitor_test.h
  muRunTest(test_depth_first);
  muRunTest(test_breadth_first);
  muRunTest(test_find_element_with_matching_attr);
  log_info("SKIPPED: test_str_one");
  // muRunTest(test_str_one);
  log_info("SKIPPED: test_str_kids");
  // muRunTest(test_str_kids);

  return NULL;
}

RUN_TESTS(allTests);
