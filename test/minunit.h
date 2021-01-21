#ifndef _minunit_h
#define _minunit_h
#include <stdio.h>
#include <stdlib.h>
#include <debug.h>

#define muSuiteStart() char *message = NULL

#define muAssert(test, message) if (!(test)) {\
    log_err(message); return message; }

#define muRunTest(test) message = test(); testsRun++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    printf("\n----\nRUNNING: %s\n", argv[0]);\
    char *result = name();\
    if (result != 0) {\
        printf("\033[1m\x1b[31mFAILED:\033[0m \x1b[31m%s\x1b[00m\n", result);\
    }\
    else {\
        printf("\033[1m\x1b[32mALL TESTS PASSED\x1b[00m\033[0m\n");\
    }\
    printf("Tests run: %d\n", testsRun);\
    exit(result != 0);\
}

int testsRun;

#endif // _minunit_h
