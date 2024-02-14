#ifndef __arena_test_h__
#define __arena_test_h__

char *test_arena_init(void);
char *test_arena_malloc(void);
char *test_arena_malloc_fail(void);
char *test_arena_malloc_reset(void);

char *test_arena_ginit(void);
char *test_arena_gmalloc(void);
char *test_arena_gmalloc_fail(void);
char *test_arena_gmalloc_reset(void);

#endif // __arena_test_h__

