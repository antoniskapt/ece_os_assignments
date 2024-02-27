# GNU Make
#
# 049 - Operating Systems
# Quiz 5
#
# Kapetanios Antonios, 10417
#
# January 2024

CC = gcc
CFLAGS = -O2 -std=gnu17
SRC = main.c vector.c
OBJ = $(SRC:.c=.o)
EXEC= bin

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

clean_objects:
	rm -f $(OBJ)
