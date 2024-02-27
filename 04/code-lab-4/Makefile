SHELL := /bin/bash


# ============================================
# COMMANDS

CC = gcc -O3
RM = rm -f

# ==========================================
# TARGETS

EXECUTABLES = pipe_1 pipe_2 signal immun2ctrlC example_sleep \
	example_pause example_kill


all: $(EXECUTABLES)


pipe_1: pipe_1.c
	$(CC) $< -o $@

pipe_2: pipe_2.c
	$(CC) $< -o $@

signal: signal.c
	$(CC) $< -o $@

immun2ctrlC: immun2ctrlC.c
	$(CC) $< -o $@

example_sleep: example_sleep.c
	$(CC) $< -o $@

example_pause: example_pause.c
	$(CC) $< -o $@

example_kill: example_kill.c
	$(CC) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLES)
