#	GNU Makefile
#
#	Kapetanios Antonios 10417
#	December 2023
#
#	049 - OS
#	hw assignment 2
CC = gcc
CFLAGS = -std=gnu17 -O2
OBJ = main.o c_proc.o sort.o
EXEC = quiz-3
LFLAGS = -lrt

BIN=~/quiz-3/bins

.PHONY: clean

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LFLAGS)

install:
	mkdir -p $(BIN)
	mv $(EXEC) $(BIN)

# patterns are not supported by BSD Make
%.o: %.c
	$(CC) -c $< -o $@ $(LFLAGS)

# removes object files, the executable and the ./bins/ directory, if it exists.
clean:
	rm $(OBJ) || true
	rm -r $(EXEC) || true
	rm -r $(BIN)/$(EXEC) || true
	rmdir $(BIN) || true

# additional rule: removes object files only.
clean_objects:
	rm $(OBJ)
