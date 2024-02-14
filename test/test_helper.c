#include "arena.h"
#include "node.h"
#include "test_helper.h"
#include <stdio.h>
#include <log.h>
#include <stdlib.h>

/**
 * Load line-delimited data from the file found at, path. Each line of data
 * will be added to the provided lines collection.
 */
void loadFixtureData(char *path, u32_t *lines) {
  FILE *file;
  file = fopen(path, "r");
  s32_t i = 0;

  if (file == NULL) {
    log_err("Error Reading File: %s\n", path);
    exit(0);
  }

  // Read file into array
  s32_t len = 1024;
  for (i = 0; i < len; i++) {
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

void init_arena(void) {
    arena_global_init(sizeof(node_t) * 100);
}

