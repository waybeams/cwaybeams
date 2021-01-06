#ifndef __dom_h__
#define __dom_h__

#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_ELEMENT_COUNT 65535
#define DEFAULT_ZERO 0
#define DEFAULT_CHAR ""

typedef unsigned long ElementId;

typedef enum ElementType {
  TypeNone = 0,
  TypeBox,
  TypeVBox,
  TypeHBox,
  TypeButton,
  TypeLink,
  TypeStyle,
  TypeApp,
  TypeWindow,
  TypeHead,
  TypeBody
} ElementType;

typedef enum AttrName {
  NoneAttr = 0,
  ChildrenAttr,
  Flex,
  HandlerAttr,
  GestureHandlerAttr,
  HFlex,
  HeightAttr,
  LayoutAttr,
  NameAttr,
  VFlex,
  WidthAttr,
  XAttr,
  YAttr,
  ZAttr
} AttrName;

#define PP_ARG_N( \
          _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, N, ...) N

/* Note 63 is removed */
#define PP_RSEQ_N()                                        \
         62, 61, 60,                                       \
         59, 58, 57, 56, 55, 54, 53, 52, 51, 50,           \
         49, 48, 47, 46, 45, 44, 43, 42, 41, 40,           \
         39, 38, 37, 36, 35, 34, 33, 32, 31, 30,           \
         29, 28, 27, 26, 25, 24, 23, 22, 21, 20,           \
         19, 18, 17, 16, 15, 14, 13, 12, 11, 10,           \
          9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define PP_NARG_(...)    PP_ARG_N(__VA_ARGS__)

/* Note dummy first argument _ and ##__VA_ARGS__ instead of __VA_ARGS__ */
#define PP_NARG(...)     PP_NARG_(_, ##__VA_ARGS__, PP_RSEQ_N())

/**
 * Wrap variadic macros with expected names.
 */
#define app(...) newElement(TypeApp, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define window(...) newElement(TypeWindow, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define box(...) newElement(TypeBox, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define vbox(...) newElement(TypeVBox, PP_NARG(__VA_ARGS__) + 1, \
    layout(LayoutVertical), __VA_ARGS__)
#define hbox(...) newElement(TypeHBox, PP_NARG(__VA_ARGS__) + 1, \
    layout(LayoutHorizontal), __VA_ARGS__)
#define children(...) newChildren(PP_NARG(__VA_ARGS__), __VA_ARGS__)

// Attribute setter macros
#define name(value) newCharAttr(NameAttr, value)
#define layout(value) newUintAttr(LayoutAttr, value)
#define width(value) newUintAttr(WidthAttr, value)
#define handler(value) newHandlerAttr(GestureHandlerAttr, value)
#define height(value) newUintAttr(HeightAttr, value)
#define x(value) newUintAttr(XAttr, value)
#define y(value) newUintAttr(YAttr, value)
#define z(value) newUintAttr(ZAttr, value)

// Attribute getter macros
#define getName(elem) getCharAttrFromElement(elem, NameAttr, DEFAULT_CHAR)
#define getLayout(elem) getUintAttrFromElement(elem, LayoutAttr, LayoutDefault)
#define getWidth(elem) getUintAttrFromElement(elem, WidthAttr, DEFAULT_ZERO)
#define getHeight(elem) getUintAttrFromElement(elem, HeightAttr, DEFAULT_ZERO)
#define getX(elem) getUintAttrFromElement(elem, XAttr, DEFAULT_ZERO)
#define getY(elem) getUintAttrFromElement(elem, YAttr, DEFAULT_ZERO)
#define getZ(elem) getUintAttrFromElement(elem, ZAttr, DEFAULT_ZERO)

typedef enum Layout {
  LayoutDefault = 0,
  LayoutStack,
  LayoutVertical,
  LayoutHorizontal,
} Layout;

/**
 * Container for arbitrary data
 * values.
 */
typedef struct Attr {
  AttrName name;
  unsigned int dataSize;
  unsigned char *data;
} Attr;

typedef struct Element {
  ElementId id;
  ElementId parentId;
  ElementType type;
  unsigned int childCount;
  unsigned int attrCount;
  struct Attr **attrs;
} Element;

typedef void (*GestureHandler)(void);

// Attribute custom factories
Element *newElement(ElementType type, unsigned int count, ...);
Attr *newChildren(unsigned int count, ...);

// Attribute type factories
Attr *newCharAttr(AttrName name, char *value);
Attr *newUintAttr(AttrName name, unsigned value);
Attr *newHandlerAttr(AttrName name, GestureHandler handler);

// Attribute type getters
struct Element **getElementsAttr(Attr *attr);
unsigned int getUintAttr(Attr *attr);
char *getCharAttr(Attr *attr);

// Element Attribute getters
// char *getName(Element *elem);
struct Element **getChildren(Element *elem);

// Element helpers
void printElement(Element *elem);
bool isRoot(Element *elem);
void emitEvent(Element *elem, char *gestureName);

// Destructors
void freeElement(Element *elem);
void freeAttr(Attr *attr);

// Used by Macros only
char *getCharAttrFromElement(Element *elem, AttrName name, char *defaultValue);
unsigned int getUintAttrFromElement(Element *elem, AttrName name,
    unsigned int defaultValue);

#endif
