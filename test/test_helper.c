#include <test_helper.h>
#include <stdio.h>
#include <debug.h>
#include <stdlib.h>

/**
 * Load line-delimited data from the file found at, path. Each line of data
 * will be added to the provided lines collection.
 */
void loadFixtureData(char *path, uint32_t *lines) {
  FILE *file;
  file = fopen(path, "r");
  int i = 0;

  if (file == NULL) {
    log_err("Error Reading File: %s\n", path);
    exit(0);
  }

  // Read file into array
  int len = 1024;
  for (i = 0; i < len; i++) {
    fscanf(file, "%d,", (int*)&lines[i]);
		if (lines[i] == '\0') {
			// debug("loaded %d fixture lines from disk\n", i);
			break;
		}
  }

  fclose(file);
}

