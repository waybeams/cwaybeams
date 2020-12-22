export

################################################################
# Makefile for C project
################################################################

# Set DEBUG=true if 'make debug'
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
DEBUG := true
endif

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

debug:
	@echo "DEBUG=true"

# Build for debug and run with Valgrind
valgrind: $(OUTFILE)
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	valgrind $(VALGRIND_FLAGS) $(OUTFILE)
else
 @echo "ERROR: Must run 'make debug valgrind'"
endif

# Build and run the debug binary
gdb: $(OUTFILE)
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	gdb -ex run $(OUTFILE)
else
	@echo "ERROR: Must run 'make debug gdb'"
endif

# Remove generated artifacts
clean:
	rm -rf dist

# Generate ctags (for vim tag completion)
ctags:
	ctags -R .
