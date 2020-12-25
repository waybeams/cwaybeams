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
  // muRunTest(testNewElement);

  return NULL;
}

RUN_TESTS(allTests);

#endif // TEST_MODE

