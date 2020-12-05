
CEE_FILES=*.c

run: example
	./dist/example

dist:
	mkdir -p ./dist

example: Makefile dist $(CEE_FILES)
	gcc -o dist/example $(CEE_FILES)
	ls -la dist/example

example-debug: Makefile dist $(CEE_FILES)
	gcc -g -o dist/example-debug $(CEE_FILES)

debug: example-debug
	gdb -ex run dist/example-debug

clean:
	rm -rf dist
