#ifndef _arena_test_h_
#define _arena_test_h_

char *test_arena_init(void);
char *test_arena_malloc(void);
char *test_arena_malloc_fail(void);
char *test_arena_malloc_reset(void);
char *test_arena_calloc(void);

char *test_arena_global_init(void);
char *test_arena_global_malloc(void);
char *test_arena_global_malloc_fail(void);
char *test_arena_global_malloc_reset(void);
char *test_arena_global_calloc(void);

#endif // _arena_test_h_
