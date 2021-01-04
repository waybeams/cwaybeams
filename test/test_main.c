#include "minunit.h"
#include <dom_test.h>
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

  // layout_test.h
  muRunTest(testNewLayout);

  return NULL;
}

RUN_TESTS(allTests);

