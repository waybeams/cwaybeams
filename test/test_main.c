#ifdef TEST_MODE

#include <minunit.h>
#include <dom_test.h>
#include <layout_test.h>

char *allTests(void) {
  // Begin the test suite
  muSuiteStart();

  // dom_test.h
  muRunTest(testNewCharAttr);
  muRunTest(testNewName);
  muRunTest(testNewHeight);
  muRunTest(testNewWidth);
  muRunTest(testNewBox);
  muRunTest(testNewBoxWithName);
  muRunTest(testNewChildren);
  muRunTest(testElementWithChild);
  muRunTest(testIsRoot);
  muRunTest(testDefaultLayout);
  muRunTest(testLayout);
  muRunTest(testHandler);

  // layout_test.h
  muRunTest(testNewLayout);

  return NULL;
}

RUN_TESTS(allTests);

#endif // TEST_MODE

