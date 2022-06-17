.PHONY: help
help:
	@cat makefile | grep -v PHONY

.PHONY: clean
clean:
	rm -f test main

test: lib.h lib.c test.c
	$ gcc -std=c11 -pedantic -Wall -Wextra -Werror test.c lib.c -otest

.PHONY: run-test
run-test: test
	./test

main: lib.h lib.c main.c
	$ gcc -std=c11 -pedantic -Wall -Wextra -Werror main.c lib.c -omain
