
DIST := dist
CEE_FILES=*.c

CFLAGS := -Wall
CFLAGS += -Werror
ifeq ($(DEBUG), true)
CFLAGS += -ggdb
CFLAGS += -O0
OUTFILE := $(DIST)/example-debug
else
CFLAGS += -Werror
CFLAGS += -Os
OUTFILE := $(DIST)/example
endif

OPT_CFLAGS := -O3

VALGRIND_FLAGS := --leak-check=full
VALGRIND_FLAGS += --show-leak-kinds=all
VALGRIND_FLAGS += --tool=memcheck
VALGRIND_FLAGS += --track-origins=yes
VALGRIND_FLAGS += --leak-resolution=high
VALGRIND_FLAGS += --show-mismatched-frees=yes
VALGRIND_FLAGS += -s

# Build and run optimized binary
run: $(OUTFILE)
		./$(OUTFILE)

# Create the dist directory
dist:
	mkdir -p ./dist

# Build the debug binary
$(OUTFILE): Makefile dist $(CEE_FILES)
	gcc $(CFLAGS) -o $(OUTFILE) $(CEE_FILES)
	ls -lah $(OUTFILE)

# Build for debug and run with Valgrind
valgrind: $(OUTFILE)
	valgrind $(VALGRIND_FLAGS) $(OUTFILE)

# Build and run the debug binary
debug: $(OUTFILE)
	gdb -ex run $(OUTFILE)

# Remove generated artifacts
clean:
	rm -rf dist

# Generate ctags (for vim tag completion)
ctags:
	ctags -R .
