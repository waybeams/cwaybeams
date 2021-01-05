#include "minunit.h"
#include <dom_test.h>
#include <dom_visitor_test.h>
#include <hfsm_test.h>
#include <layout_test.h>

char *allTests(void) {
  // Begin the test suite
  muSuiteStart();

  // dom_test.h
  muRunTest(testNewCharAttr);
  muRunTest(testNewNameAttr);
  muRunTest(testNewHeight);
  muRunTest(testNewWidth);
  muRunTest(testNewLargerWidth);
  muRunTest(testNewBox);
  muRunTest(testNewBoxWithName);
  muRunTest(testNewChildren);
  muRunTest(testElementWithChild);
  muRunTest(testIsRoot);
  muRunTest(testGetName);
  muRunTest(testDefaultLayout);
  muRunTest(testLayout);
  muRunTest(testHandler);
  muRunTest(testDefaultAttrValues);
  muRunTest(testConfiguredAttrValues);
  muRunTest(testAttrCollection);
  muRunTest(testElementTypes);

  // dom_visitor_test.h
  muRunTest(testDepthFirst);

  // layout_test.h
  muRunTest(testNewLayout);

  // hfsm_test.h
  muRunTest(test_hfsm_creation);

  return NULL;
}

RUN_TESTS(allTests);

