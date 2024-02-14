#include "arena.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arena_t {
  size_t size;
  size_t used;
  u8_t *data;
} arena_t;

static arena_t global_arena = {0};

s8_t arena_ginit(size_t size) {
  if (global_arena.data != NULL) {
    printf("arena_init: already initialized\n");
    return -1;
  }

  global_arena.size = size;
  global_arena.used = 0;
  global_arena.data = malloc(size);
  if (global_arena.data == NULL) {
    printf("arena_new: malloc failed\n");
    return -1;
  }

  return 0;
}

void *arena_gmalloc(size_t size) {
  if (global_arena.used + size > global_arena.size) {
    printf("arena_malloc: out of memory\n");
    return NULL;
  }

  void *ptr = global_arena.data + global_arena.used;
  global_arena.used += size;
  return ptr;
}

void *arena_gcalloc(size_t size, u32_t count) {
  u64_t total = size * count;
  if (total > SIZE_MAX) {
    printf("arena_calloc: size too large\n");
    return NULL;
  }

  void *ptr = arena_gmalloc(total);
  if (ptr == NULL) {
    return NULL;
  }

  memset(ptr, 0, total);
  return ptr;
}

void arena_greset(void) {
  global_arena.used = 0;
}

void arena_gfree(void) {
  if (global_arena.data == NULL) {
    printf("arena_free called, but not initialized\n");
    return;
  }
  free(global_arena.data);
  global_arena.data = NULL;
}
