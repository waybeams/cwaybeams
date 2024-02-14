#include "arena.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

arena_t arena_new(size_t size) {
  arena_t a = {0};
  if (arena_init(&a, size) != 0) {
    log_fatal("arena_new: failed to initialize\n");
  }

  return a;
}

s8_t arena_init(arena_t *a, size_t size) {
  if (a == NULL) {
    log_fatal("arena_init called with NULL context\n");
    return -1;
  }
  a->data = malloc(size);
  if (a->data == NULL) {
    log_fatal("arena_init: failed to allocate\n");
    return -1;
  }

  a->size = size;
  a->used = 0;
  return 0;
}

void *arena_malloc(arena_t *a, size_t size) {
  if (a == NULL || a->size == 0) {
    log_fatal("arena_init() must be called before malloc or calloc\n");
    exit(1);
  }

  if (a->used + size > a->size) {
    log_fatal("arena_malloc requested %ld, but only had %ld remaining from %ld bytes\n", size, a->size -
      a->used, a->size);
    return NULL;
  }

  void *ptr = a->data + a->used;
  a->used += size;
  return ptr;
}

void *arena_calloc(arena_t *a, size_t size, u32_t count) {
  if (a == NULL || a->size == 0) {
    log_fatal("arena_init() must be called before malloc or calloc\n");
    exit(1);
  }

  u64_t total = size * count;
  if (total > SIZE_MAX) {
    log_fatal("arena_calloc: size too large\n");
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

void arena_free(arena_t *a) {
  if (a->data == NULL || a->size == 0) {
    log_fatal("arena_free called, but not initialized\n");
    return;
  }
  free(a->data);
  a->data = NULL;
}

