
CEE_FILES=*.c

run: example
	./example

example: Makefile $(CEE_FILES)
	gcc -o example $(CEE_FILES)

clean:
	rm example
