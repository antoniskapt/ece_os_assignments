# GNU Make
#
# 049 - Operating Systems
# Quiz 5
#
# Kapetanios Antonios, 10417
#
# January 2024

CC=gcc
CFLAGS=-Wall -Wextra -std=gnu17
# References:
# https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html#index-fpic
# https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Link-Options.html#Link%20Options
PIC=-fpic

.PHONY: runner lib clean test

# ==================
# Auxiliary recipies
# ==================

# Recipe to compile the shared library
lib: libdummy.c
	$(CC) -c $(CFLAGS) $(PIC) libdummy.c
	$(CC) -shared -o libdummy.so libdummy.o

# =================
# Required recipies
# =================

runner: lib runner.c
	$(CC) -L. -Wl,-rpath=. $(CFLAGS) -o runner.out runner.c -ldummy

test: lib test_runner.c
	$(CC) -L. -Wl,-rpath=. $(CFLAGS) -o test_runner.out test_runner.c -ldummy
	./test_runner.out

clean:
	rm -f *.o *.so *.out