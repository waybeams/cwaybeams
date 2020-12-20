
CEE_FILES=*.c

CFLAGS := -Wall
CFLAGS += -Werror

DEBUG_CFLAGS := -g
DEBUG_CFLAGS += -O0

OPT_CFLAGS := -O3

VALGRIND_FLAGS := --leak-check=full
VALGRIND_FLAGS += --tool=memcheck
VALGRIND_FLAGS += --track-origins=yes
VALGRIND_FLAGS += --leak-resolution=high
VALGRIND_FLAGS += --show-mismatched-frees=yes
VALGRIND_FLAGS += -s

# Build and run optimized binary
run: example-optimize
		./dist/example-optimize

# Create the dist directory
dist:
	mkdir -p ./dist

# Build the debug binary
example-debug: Makefile dist $(CEE_FILES)
	gcc $(DEBUG_CFLAGS) $(CFLAGS) -o dist/example-debug $(CEE_FILES)

# Build the optimized binary
example-optimize: Makefile dist $(CEE_FILES)
	gcc $(OPT_FLAGS) $(CFLAGS) -o dist/example-optimize $(CEE_FILES)
	ls -lah dist/example-optimize

# Build for debug and run with Valgrind
valgrind: example-debug
	valgrind $(VALGRIND_FLAGS) dist/example-debug

# Build and run the debug binary
debug: example-debug
	gdb -ex run dist/example-debug

# Remove generated artifacts
clean:
	rm -rf dist

# Generate ctags (for vim tag completion)
ctags:
	ctags -R .
