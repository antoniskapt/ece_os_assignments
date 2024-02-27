#	GNU Makefile
#
#	Kapetanios Antonios 10417
#	December 2023
#
#	049 - OS
#	hw assignment 4
CC = gcc
CFLAGS = -std=gnu17 -O2
OBJ1 = mysigcatch.o
OBJ2 = mysigcatchmodified.o

.PHONY: clean

all: mysigcatch mysigcatchmodified

mysigcatch: $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o mysigcatch

mysigcatchmodified: $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o mysigcatchmodified

%.o: %.c
	$(CC) -c $< -o $@

# removes object files and the executables.
clean:
	rm -f $(OBJ1) $(OBJ2) mysigcatch mysigcatchmodified

# removes object files only.
clean_objects:
	rm -f $(OBJ1) $(OBJ2)
