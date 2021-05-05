#include "hash_test.h"
#include "fast_hash.h"
#include "minunit.h"
#include <stdint.h>

#define HASH_ABCD 3671636187

char *test_new_hash(void) {
  uint32_t h = fast_hash("abcd", 4);
  muAssert(h == HASH_ABCD, "Expected abcd hash");
  return NULL;
}
