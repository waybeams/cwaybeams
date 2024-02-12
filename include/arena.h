#ifndef __arena_h__
#define __arena_h__

#include "node.h"

s8_t arena_init(size_t size);

void arena_free(void);

void *arena_alloc(size_t size);

void arena_reset(void);

#endif // __arena_h__

