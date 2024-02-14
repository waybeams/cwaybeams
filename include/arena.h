#ifndef __arena_h__
#define __arena_h__

#include "node.h"

s8_t arena_ginit(size_t size);

void arena_gfree(void);

void *arena_gmalloc(size_t size);

void *arena_gcalloc(size_t size, u32_t count);

void arena_greset(void);

#endif // __arena_h__

