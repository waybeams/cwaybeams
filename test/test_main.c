#ifdef TEST_MODE

#include <minunit.h>
#include <dom_test.h>

char *allTests(void) {
  // Begin the test suite
  muSuiteStart();

  muRunTest(testNewCharAttr);
  muRunTest(testNewName);
  muRunTest(testNewHeight);
  muRunTest(testNewWidth);
  muRunTest(testNewBox);
  muRunTest(testNewBoxWithName);
  muRunTest(testNewChildren);
  // muRunTest(testElementWithChild);

  return NULL;
}

RUN_TESTS(allTests);

#endif // TEST_MODE

