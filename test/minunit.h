#ifndef __MINUNIT_H__
#define __MINUNIT_H__

#include <stdio.h>
#include <stdlib.h>
#include <log.h>

#ifdef __GNUC__
#define MINUNIT_ATTR_IS_USED __attribute__ ((unused))
#else
#define MINUNIT_ATTR_IS_USED
#endif

MINUNIT_ATTR_IS_USED static int minunit_tests_run = 0;

#define muSuiteStart() char *message = NULL

#define muAssert(test, message) if (!(test)) {\
    log_err(message); return message; }

#define muRunTest(test) message = test(); minunit_tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) { \
    printf("\n----\nRUNNING: %d %s\n", argc, argv[0]);\
    char *result = name();\
    if (result != 0) {\
        printf("\033[1m\x1b[31mFAILED:\033[0m \x1b[31m%s\x1b[00m\n", result);\
    }\
    else {\
        printf("\033[1m\x1b[32mALL TESTS PASSED\x1b[00m\033[0m\n");\
    }\
    printf("Tests run: %d\n", minunit_tests_run);\
    exit(result != 0);\
}

#endif // __minunit_h__
