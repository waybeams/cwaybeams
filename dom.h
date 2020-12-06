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

typedef enum Layout {
  LAYOUT_STACK = 0,
  LAYOUT_VERTICAL,
  LAYOUT_HORIZONTAL,
} Layout;

typedef struct Element {
  ElementId id;
  ElementId parentId;
  char* name;
  Layout layout;
  unsigned int width;
  unsigned int height;
  unsigned int childCount;
  ElementId *children;
} Element;

typedef struct Context {
  Element nextElement;
  Element elements[MAX_ELEMENT_COUNT];
  int lastElementIndex;
  int lastRelationIndex;
  ElementId *pendingChildren;
  unsigned int pendingChildCount;
} Context;

// Properties
uint8_t name(Context *ctx, char*);
uint8_t width(Context *ctx, unsigned int w);
uint8_t height(Context *ctx, unsigned int h);
uint8_t children(Context *ctx, unsigned int count, ...);

// Entities
unsigned int vbox(Context *ctx, ...);
unsigned int hbox(Context *ctx, ...);
unsigned int box(Context *ctx, ...);

void printElement(Element *elem);
void begin(Context *ctx);
void end(Context *ctx);

#endif
