#include "arena_test.h"
#include "arena.h"
#include "minunit.h"

char *test_arena_init(void) {
  s8_t status = arena_init(1024);
  muAssertIntEq(status, 0, "arena_init: arena initialized");

  arena_free();
  return NULL;
}

char *test_arena_malloc(void) {
  s8_t status = arena_init(1024);
  muAssertIntEq(status, 0, "arena_init: arena initialized");
  void *ptr = arena_malloc(128);
  muAssert(ptr != NULL, "arena_malloc: ptr is NULL");

  arena_free();
  return NULL;
}

char *test_arena_malloc_fail(void) {
  arena_init(128);
  void *ptr = arena_malloc(128);
  muAssert(ptr != NULL, "arena_malloc: ptr is NULL");

  void *fail = arena_malloc(1);
  muAssert(fail == NULL, "Expected failure to allocate");

  arena_free();
  return NULL;
}

char *test_arena_malloc_reset(void) {
  arena_init(128);
  u64_t *one = arena_malloc(sizeof(u64_t));
  *one = 11;
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  arena_reset();
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  u64_t *two = arena_malloc(sizeof(u64_t));
  *two = 22;
  muAssertLongEq(*two, 22L, "Expected two to be 22");
  muAssertLongEq(*one, 22L, "The one pointer is no longer valid");

  arena_free();
  return NULL;
}
