#include "arena_test.h"
#include "arena.h"
#include "minunit.h"

char *test_arena_init(void) {
  s8_t status = arena_ginit(1024);
  muAssertIntEq(status, 0, "arena_ginit: arena initialized");

  arena_gfree();
  return NULL;
}

char *test_arena_gmalloc(void) {
  s8_t status = arena_ginit(1024);
  muAssertIntEq(status, 0, "arena_ginit: arena initialized");
  void *ptr = arena_gmalloc(128);
  muAssert(ptr != NULL, "arena_gmalloc: ptr is NULL");

  arena_gfree();
  return NULL;
}

char *test_arena_gmalloc_fail(void) {
  arena_ginit(128);
  void *ptr = arena_gmalloc(128);
  muAssert(ptr != NULL, "arena_gmalloc: ptr is NULL");

  void *fail = arena_gmalloc(1);
  muAssert(fail == NULL, "Expected failure to allocate");

  arena_gfree();
  return NULL;
}

char *test_arena_gmalloc_reset(void) {
  arena_ginit(128);
  u64_t *one = arena_gmalloc(sizeof(u64_t));
  *one = 11;
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  arena_greset();
  muAssertLongEq(*one, 11L, "Expected one to be 11");

  u64_t *two = arena_gmalloc(sizeof(u64_t));
  *two = 22;
  muAssertLongEq(*two, 22L, "Expected two to be 22");
  muAssertLongEq(*one, 22L, "The one pointer is no longer valid");

  arena_gfree();
  return NULL;
}
