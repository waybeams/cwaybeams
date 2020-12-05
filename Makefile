
CEE_FILES=*.c

run: example
	./dist/example

dist:
	mkdir -p ./dist

example: Makefile dist $(CEE_FILES)
	gcc -Wall -Werror -o dist/example $(CEE_FILES)
	ls -lah dist/example

example-debug: Makefile dist $(CEE_FILES)
	gcc -g -Wall -Werror -o dist/example-debug $(CEE_FILES)

example-optimize: Makefile dist $(CEE_FILES)
	gcc -O3 -o dist/example-optimize $(CEE_FILES)
	ls -lah dist/example-optimize

debug: example-debug
	gdb -ex run dist/example-debug

clean:
	rm -rf dist
