# CWAYBEAMS
_(Pronounced, "Sway-beems")_

This is not a thing. I'm just exploring some ideas in order to learn c.

If you're curious about what it might do or be, check out [examples/*](examples)

Also, check out the [blog](blog) for more info.

# Getting Started
Here's how I build and run for development and testing:

```bash
premake5 gmake && \
make && \
valgrind ./dist/Debug/beam-test
```

# File Watcher
```bash
when-changed.py \
  src/* \
  include/* \
  test/* examples/*  \
  -c "premake5 gmake && \
    make && valgrind \
    ./dist/Debug/beam-test"
```

# Debugging
Here's how I build and run with GDB:

```bash
premake5 gmake && \
make clean && \
make && \
gdb ./dist/Debug/beam-test
```
