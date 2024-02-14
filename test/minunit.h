#ifndef ANGLES_MINUNIT_H_
#define ANGLES_MINUNIT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

#define MINUNIT_DBL_EPSILON 0.000001

#ifdef __GNUC__
#define MINUNIT_ATTR_IS_USED __attribute__ ((unused))
#else
#define MINUNIT_ATTR_IS_USED
#endif

MINUNIT_ATTR_IS_USED static int minunit_tests_run = 0;

#define muSuiteStart() char *message = NULL

#define muAssert(test, message) if (!(test)) {\
    log_err_minunit(message); return message; }

#define muAssertNull(a, message) if ((a) != NULL) {\
    log_err_minunit("%s [%p != NULL]", message, &(a)); return message; }

#define muAssertDoubleEqToDec(a, b, dec, message) if (fabs((a) - (b)) > (dec)) {\
    log_err_minunit("%s [%.16lf != %.16lf]", message, (a), (b)); return message; }

#define muAssertFloatEq(a, b, message) if (fabs((a) - (b)) > MINUNIT_DBL_EPSILON) {\
    log_err_minunit("%s [%.8f != %.8f]", message, (a), (b)); return message; }

#define muAssertDoubleEq(a, b, message) if (abs((a) - (b)) > MINUNIT_DBL_EPSILON) {\
    log_err_minunit("%s [%.16lf != %.16lf]", message, (a), (b)); return message; }

#define muAssertIntEq(a, b, message) if ((a) != (b)) {\
    log_err_minunit("%s [%d != %d] or [0x%x != 0x%x]", message, (a), (b), (a), (b)); return message; }

#define muAssertSizeEq(a, b, message) if ((a) != (b)) {\
    log_err_minunit("%s [%zu != %zu]", message, (a), (b)); return message; }

#define muAssertLongEq(a, b, message) if ((a) != (b)) {\
    log_err_minunit("%s [%ld != %ld]", message, (a), (b)); return message; }

#define muAssertLongLongEq(a, b, message) if ((a) != (b)) {\
    log_err_minunit("%s [%lu != %lu]", message, (a), (b)); return message; }

#define muAssertStrEq(a, b, message) if (strcmp((char *)(a), (char *)(b)) != 0) {\
    log_err_minunit("%s \"%s\" != \"%s\"", message, (a), (b)); return message; }

#define muAssertSubstrEq(a, b, len, message) if (strncmp((char *)(a), (char *)(b), (len)) != 0) {\
    log_err_minunit("%s \"%s\" != \"%s\"", message, (a), (b)); return message; }

#define muAssertCharEq(a, b, message) if ((a) != (b)) {\
    log_err_minunit("%s \"%c\" != \"%c\"", message, (a), (b)); return message; }

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

#endif // ANGLES_MINUNIT_H_
