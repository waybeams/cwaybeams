#ifndef __dom_h__
#define __dom_h__

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_ELEMENT_COUNT 65535

static unsigned int lastId = 0;
static unsigned int nextId(void);

typedef struct Element {
  unsigned int id;
  char* name;
  unsigned int width;
  unsigned int height;
} Element;

typedef struct Context {
  Element* nextElement;
  int lastIndex;
  Element* elements[MAX_ELEMENT_COUNT];
} Context;

uint8_t name(char*);
uint8_t width(unsigned int);
uint8_t height(unsigned int);

uint8_t box(Context *ctx, ...);
uint8_t children(Context *ctx, ...);

#endif
