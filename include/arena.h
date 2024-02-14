#ifndef __arena_h__
#define __arena_h__

#include "node.h"

s8_t arena_init(size_t size);

void arena_free(void);

void *arena_malloc(size_t size);

void *arena_calloc(size_t size, u32_t count);

void arena_reset(void);

#endif // __arena_h__

