#ifndef _test_helper_h_
#define _test_helper_h_

#include <stdint.h>

/**
 * Load line-delimited data from the file found at, path. Each line of data
 * will be added to the provided lines collection.
 */
void loadFixtureData(char *path, uint32_t *lines);

void init_arena(void);

#endif // _test_helper_h__
