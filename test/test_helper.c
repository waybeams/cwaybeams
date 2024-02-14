#include "arena.h"
#include "log.h"
#include "node.h"
#include "test_helper.h"
#include <stdlib.h>

/**
#include <stdio.h>
#include <log.h>
#include <stdlib.h>

 * Load line-delimited data from the file found at, path. Each line of data
 * will be added to the provided lines collection.
void loadFixtureData(char *path, u32_t *lines) {
  FILE *file;
  file = fopen(path, "r");

  if (file == NULL) {
    log_err("Error Reading File: %s\n", path);
    exit(0);
  }

  // Read file into array
  s32_t len = 1024;
  for (s32_t i = 0; i < len; i++) {
    s32_t result = fscanf(file, "%d,", (s32_t*)&lines[i]);
    if (result != 0) {
      fprintf(stderr, "fscanf failed with: %d\n", result);
    }
		if (lines[i] == '\0') {
			// debug("loaded %d fixture lines from disk\n", i);
			break;
		}
  }

  fclose(file);
}
*/

static arena_t *module_arena = NULL;
void setup_arena(size_t size) {
  module_arena = malloc(sizeof(arena_t));
  if (module_arena == NULL) {
    log_fatal("Failed to allocate memory for module_arena\n");
    exit(1);
  }
  arena_init(module_arena, size == 0 ? DEFAULT_ARENA_SIZE : size);
  node_set_arena(module_arena);
}

void teardown_arena(void) {
  arena_free(module_arena);
  free(module_arena);
  module_arena = NULL;
}
