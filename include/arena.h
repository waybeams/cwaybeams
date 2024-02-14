#ifndef _arena_h_
#define _arena_h_

#include "node.h"

typedef struct arena_t {
  size_t size;
  size_t used;
  u8_t *data;
} arena_t;

//------------------------------------------------------------------------------
// Instance Arena
//------------------------------------------------------------------------------

/**
 * Initialize the arena with the provided number of bytes.
 */
s8_t arena_init(arena_t *a, size_t size);

/**
 * Allocate memory from the provided arena.
 */
void *arena_malloc(arena_t *a, size_t size);

/**
 * Allocate and zero memory from the provided arena.
 */
void *arena_calloc(arena_t *a, size_t size, u32_t count);

/**
 * Reset the provided arena.
 */
void arena_reset(arena_t *a);

/**
 * Free the provided arena.
 */
void arena_free_all(arena_t *a);

//------------------------------------------------------------------------------
// Global / Module Arena
//------------------------------------------------------------------------------

/**
 * Initialize the global module-scope arena with the provide number of bytes.
 *
 * @return NULL if malloc fails, otherwise a pointer to the arena.
 */
s8_t arena_global_init(size_t size);

/**
 * Free the global module-scope arena.
 */
void arena_global_free_all(void);

/**
 * Allocate memory from the global module-scope arena.
 */
void *arena_global_malloc(size_t size);

/**
 * Allocate and zero memory from the global module-scope arena.
 */
void *arena_global_calloc(size_t size, u32_t count);

/**
 * Reset the global module-scope arena.
 */
void arena_global_reset(void);

#endif // _arena_h_
