#ifndef __dom_h__
#define __dom_h__

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_ELEMENT_COUNT 65535

typedef enum Layout {
  LAYOUT_STACK = 0,
  LAYOUT_VERTICAL,
  LAYOUT_HORIZONTAL,
} Layout;

typedef struct Element {
  unsigned int id;
  char* name;
  Layout layout;
  unsigned int width;
  unsigned int height;
} Element;

typedef struct Context {
  Element nextElement;
  int lastIndex;
  Element elements[MAX_ELEMENT_COUNT];
} Context;

uint8_t name(Context *ctx, char*);
uint8_t width(Context *ctx, unsigned int);
uint8_t height(Context *ctx, unsigned int);

uint8_t vbox(Context *ctx, ...);
uint8_t hbox(Context *ctx, ...);
uint8_t children(Context *ctx, ...);

void printElement(Element *elem);

#endif
