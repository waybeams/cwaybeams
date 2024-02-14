#include "arena_test.h"
#include "arena.h"
#include "minunit.h"

char *test_arena_init(void) {
  arena_t a = {0};
  s8_t status = arena_init(&a, 1024);
  muAssertIntEq(status, 0, "arena_global_init: arena initialized");

  arena_free_all(&a);
  return NULL;
}

char *test_arena_malloc(void) {
  arena_t a = {0};
  s8_t status = arena_init(&a, 1024);
  muAssertIntEq(status, 0, "arena_init: arena initialized");
  void *ptr = arena_malloc(&a, 128);
  muAssert(ptr != NULL, "arena_malloc: ptr is NULL");

  arena_free_all(&a);
  return NULL;
}

char *test_arena_malloc_fail(void) {
  arena_t a = {0};
  arena_init(&a, 128);
  void *ptr = arena_malloc(&a, 128);
  muAssert(ptr != NULL, "arena_malloc: ptr is NULL");

  void *fail = arena_malloc(&a, 1);
  muAssert(fail == NULL, "Expected failure to allocate");
  arena_free_all(&a);
  return NULL;
}

char *test_arena_calloc(void) {
  arena_t a = {0};
  s8_t status = arena_init(&a, 1024);
  muAssertIntEq(status, 0, "arena_init: arena initialized");
  s32_t *ptr = arena_calloc(&a, 4, 1);
  muAssert(ptr != NULL, "arena_malloc: ptr is NULL");
  muAssertIntEq(*ptr, 0, "Expected data to be zeros");

  arena_free_all(&a);
  return NULL;
}

char *test_arena_malloc_reset(void) {
  arena_t a = {0};
  arena_init(&a, 128);
  u64_t *one = arena_malloc(&a, sizeof(u64_t));
  *one = 11;
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  arena_reset(&a);
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  u64_t *two = arena_malloc(&a, sizeof(u64_t));
  *two = 22;
  muAssertLongEq(*two, 22L, "Expected two to be 22");
  muAssertLongEq(*one, 22L, "The one pointer is no longer valid");

  arena_free_all(&a);
  return NULL;
}

char *test_arena_global_init(void) {
  s8_t status = arena_global_init(1024);
  muAssertIntEq(status, 0, "arena_global_init: arena initialized");

  arena_global_free_all();
  return NULL;
}

char *test_arena_global_malloc(void) {
  s8_t status = arena_global_init(1024);
  muAssertIntEq(status, 0, "arena_global_init: arena initialized");
  void *ptr = arena_global_malloc(128);
  muAssert(ptr != NULL, "arena_global_malloc: ptr is NULL");

  arena_global_free_all();
  return NULL;
}

char *test_arena_global_malloc_fail(void) {
  arena_global_init(128);
  void *ptr = arena_global_malloc(128);
  muAssert(ptr != NULL, "arena_global_malloc: ptr is NULL");

  void *fail = arena_global_malloc(1);
  muAssert(fail == NULL, "Expected failure to allocate");

  arena_global_free_all();
  return NULL;
}

char *test_arena_global_malloc_reset(void) {
  arena_global_init(128);
  u64_t *one = arena_global_malloc(sizeof(u64_t));
  *one = 11;
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  arena_global_reset();
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  u64_t *two = arena_global_malloc(sizeof(u64_t));
  *two = 22;
  muAssertLongEq(*two, 22L, "Expected two to be 22");
  muAssertLongEq(*one, 22L, "The one pointer is no longer valid");

  arena_global_free_all();
  return NULL;
}

char *test_arena_global_calloc(void) {
  s8_t status = arena_global_init(1024);
  muAssertIntEq(status, 0, "arena_init: arena initialized");
  s32_t *ptr = arena_global_calloc(4, 1);
  muAssert(ptr != NULL, "arena_malloc: ptr is NULL");
  muAssertIntEq(*ptr, 0, "Expected data to be zeros");

  arena_global_free_all();
  return NULL;
}
