#ifndef __dom_h__
#define __dom_h__

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Context {
} Context;


uint8_t name(char*);
uint8_t width(int);
uint8_t height(int);

uint8_t box(Context *ctx, ...);
uint8_t children(Context *ctx, ...);

#endif
