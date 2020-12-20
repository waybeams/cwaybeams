#ifndef __dom_h__
#define __dom_h__

#include <stdint.h>
#include <limits.h>

#define MAX_ELEMENT_COUNT 65535

// Make variadic functions work without forcing developers to
// indicate the number of variable arguments.
//
// Implementation shamelessly copied from here:
//   https://modelingwithdata.org/arch/00000022.htm
#define varad_head(type, name) \
         type variadic_##name(variadic_type_##name x)

#define varad_declare(type, name, ...) \
        typedef struct {            \
                    __VA_ARGS__       ;  \
                } variadic_type_##name;     \
    varad_head(type, name);

#define varad_var(name, value) name = x.name ? x.name : (value);
#define varad_link(name,...) \
        variadic_##name((variadic_type_##name) {__VA_ARGS__})

typedef unsigned int ElementId;

typedef enum AttrName {
  None = 0,
  Children,
  Flex,
  HFlex,
  HPercent,
  Height,
  Name,
  VFlex,
  VPercent,
  Width,
  XOffset,
  XPos,
  YOffset,
  YPos
} AttrName;

typedef enum Layout {
  LAYOUT_DEFAULT = 0,
  LAYOUT_STACK,
  LAYOUT_VERTICAL,
  LAYOUT_HORIZONTAL,
} Layout;

typedef struct Element {
  ElementId id;
  ElementId parentId;
  Layout layout;
  unsigned int width;
  unsigned int height;
  unsigned int childCount;
  char *name;
  struct Element *children;
} Element;

typedef struct Attr {
  AttrName name;
  unsigned int uIntValue;
  int intValue;
  float floatValue;
  char *charValue;
  Element *children;
} Attr;

typedef struct Context {
  Element *elements[MAX_ELEMENT_COUNT];
  Element *pending;
} Context;

// Attributes
Attr *name(char*);
Attr *width(unsigned int w);
Attr *height(unsigned int h);
Attr *children(unsigned int count, ...);

Element *newElement(unsigned int count, ...);

// Entities
// Element* vbox(...);
// Element* hbox(...);
// Element* box(...);

void printElement(Element *elem);
void freeElement(Element *elem);

#endif
