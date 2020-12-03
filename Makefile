
CEE_FILES=*.c

run: example
	./example

example: Makefile $(CEE_FILES)
	gcc -o example $(CEE_FILES)
	ls -la ./example

clean:
	rm example
