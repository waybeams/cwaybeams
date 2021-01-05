#ifndef __dom_test_h__
#define __dom_test_h__

#include <dom.h>

char *testNewCharAttr(void);
char *testNewUintAttr(void);

char *testNewNameAttr(void);
char *testNewHeight(void);
char *testNewWidth(void);
char *testNewLargerWidth(void);

char *testNewBox(void);
char *testNewBoxWithName(void);

char *testNewChildren(void);
char *testElementWithChild(void);

char *testGetName(void);
char *testIsRoot(void);
char *testLayout(void);
char *testDefaultLayout(void);
char *testDefaultAttrValues(void);
char *testConfiguredAttrValues(void);
char *testHandler(void);

char *testAttrCollection(void);
char *testElementTypes(void);
char *testElementChildren(void);

#endif // __dom_test_h__
