# CWAYBEAMS
_(Pronounced, "Sway-beems")_

This is not a thing. I'm just exploring some ideas in order to learn c.

If you're curious about what it might do or be, check out [examples/*](examples)

Also, check out the [blog](blog) for more info.

# Getting Started
Here's how I build and run for development and testing:

```bash
cmake . && \
make && \
./bin/cwaybeams-test && \
valgrind ./bin/cwaybeams-test
```

# Debugging
Here's how I build and run with GDB:

```bash
make clean && \
cmake -DCMAKE_BUILD_TYPE=Debug . && \
make && \
gdb ./bin/cwaybeams-test
```
