#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static arena_t global_arena = {0};

s8_t arena_init(arena_t *a, size_t size) {
  a->data = malloc(size);
  if (a->data == NULL) {
    printf("arena_init: failed to allocate\n");
    return -1;
  }

  a->size = size;
  a->used = 0;
  return 0;
}

void *arena_malloc(arena_t *a, size_t size) {
  if (a->used + size > a->size) {
    printf("arena_malloc: out of memory\n");
    return NULL;
  }

  void *ptr = a->data + a->used;
  a->used += size;
  return ptr;
}

void *arena_calloc(arena_t *a, size_t size, u32_t count) {
  u64_t total = size * count;
  if (total > SIZE_MAX) {
    printf("arena_calloc: size too large\n");
    return NULL;
  }

  void *ptr = arena_malloc(a, total);
  if (ptr == NULL) {
    return NULL;
  }

  memset(ptr, 0, total);
  return ptr;
}

void arena_reset(arena_t *a) {
  a->used = 0;
}

void arena_free_all(arena_t *a) {
  if (a->data == NULL) {
    printf("arena_free_all called, but not initialized\n");
    return;
  }
  free(a->data);
  a->data = NULL;
}

s8_t arena_global_init(size_t size) {
  return arena_init(&global_arena, size);
}

void *arena_global_malloc(size_t size) {
  return arena_malloc(&global_arena, size);
}

void *arena_global_calloc(size_t size, u32_t count) {
  return arena_calloc(&global_arena, size, count);
}

void arena_global_reset(void) {
  arena_reset(&global_arena);
}

void arena_global_free_all(void) {
    arena_free_all(&global_arena);
}
