export

################################################################
# Makefile for C project
################################################################

.PHONY: test

# Set DEBUG=true if 'make debug'
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
DEBUG		:= true
endif

PROJDIR		:= $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PROJNAME	:= cwaybeam

GL_SO		:= vendor/gl/libGL.so.1.7.0
GLFW_SO		:= vendor/glfw/src/libglfw.so

DIST		:= dist

CEE_FILES	:= src/*.c
CEE_FILES	+= $(GL_SO)
CEE_FILES	+= $(GLFW_SO)

CEE_MAIN	:= examples/main.c

INCDIR		:= include

TEST_INC	:= test
TEST_FILES  := test/*.c
TESTBIN		:= $(DIST)/$(PROJNAME)-test

CFLAGS		:= -Wall
CFLAGS		+= -I$(INCDIR)
CFLAGS		+= -Ivendor/gl/include
CFLAGS		+= -Ivendor/glfw/include

# GL & GLFW headers
# -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lXcursor
# CFLAGS		+= -lXrandr
# CFLAGS		+= -lXi
# CFLAGS		+= -lXinerama
# CFLAGS		+= -lXcursor
# CFLAGS		+= -lX11
# CFLAGS		+= -lXxf86vm
# CFLAGS		+= -lpthread
# CFLAGS		+= -IGLU
# CFLAGS		+= -lGL
# CFLAGS		+= -l:libGL.so
# CFLAGS		+= -l:libglfw.so
# CFLAGS		+= -lglfw

TESTFLAGS	:= $(CFLAGS)
TESTFLAGS	+= -I$(TEST_INC)
TESTFLAGS	+= -I$(INCDIR)

TESTFLAGS	+= -DTEST_MODE
TESTFLAGS	+= -fsanitize=leak
TESTFLAGS	+= -Wunused
TESTFLAGS	+= -lm
TESTFLAGS	+= -ggdb

ifeq ($(DEBUG), true)
CFLAGS		+= -ggdb
CFLAGS		+= -O0
OUTFILE		:= $(DIST)/$(PROJNAME)-dbg
else
CFLAGS		+= -Werror
CFLAGS		+= -Os
OUTFILE		:= $(DIST)/$(PROJNAME)
endif

VALG_FLAGS	:= --leak-check=full
VALG_FLAGS	+= --show-leak-kinds=all
VALG_FLAGS	+= --tool=memcheck
VALG_FLAGS	+= --track-origins=yes
VALG_FLAGS	+= --leak-resolution=high
VALG_FLAGS	+= --show-mismatched-frees=yes
VALG_FLAGS	+= -s

# Build and run optimized binary
run: $(OUTFILE)
	./$(OUTFILE)

# Create the dist directory
dist:
	mkdir -p ./dist

# Build the debug binary
$(OUTFILE): Makefile dist $(CEE_FILES) $(CEE_MAIN)
	gcc $(CFLAGS) \
		-o $(OUTFILE) \
		$(CEE_MAIN) \
		$(CEE_FILES)
	ls -lah $(OUTFILE)

debug:
	@echo "DEBUG=true"

# Build for debug and run with Valgrind
valgrind: $(OUTFILE)
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	valgrind $(VALG_FLAGS) $(OUTFILE)
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

# Built and run tests
test: dist $(CEE_FILES) $(TEST_FILES)
	gcc $(TESTFLAGS) \
		-o $(TESTBIN) \
		$(CEE_FILES) \
		$(TEST_FILES)
		@echo $(TESTBIN)
	./$(TESTBIN)

# Remove generated artifacts
clean:
	rm -rf dist

# Generate ctags (for vim tag completion)
ctags:
	ctags -R .

# Print the linker search path to stdout
ld-path:
	ld --verbose | grep SEARCH_DIR | tr -s ' ;' \\012

