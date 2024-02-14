#ifndef _test_helper_h_
#define _test_helper_h_

#include <stdint.h>

/**
 * Load line-delimited data from the file found at, path. Each line of data
 * will be added to the provided lines collection.
 */
// void loadFixtureData(char *path, uint32_t *lines);

// 1MB of memory for default test arena
#define DEFAULT_ARENA_SIZE (1024 * 1024)

void setup_arena(size_t size);
void teardown_arena(void);

#endif // _test_helper_h__
