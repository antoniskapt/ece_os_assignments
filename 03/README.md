# Quiz 3

1. In a small C code, create 4 different processes with the right usage of `fork()`, where each process will receive a character the user types in. After all processes have acquired their character, they print the summary in ascending order and exit. Their order originates from their global process id (PID). 
	```
	I am child process 1 and my character was c. 
	I am child process 2 and my character was h.
	I am child process 3 and my character was 4.
	I am child process 4 and my character was d.
	```
	
	Your code should be split in at least two different `.c` files.

2. Also provide a Makefile that
	1. compiles your code into a single executable with `make all`,
	1. cleans reproducible and intermediate files with `make clean` and
	1. installs the binary into `/home/deadpool/quiz-3/bins/`, for user `deadpool` with `make install`. You can use either Make or CMake.

All files should live under `/home/deadpool/quiz-3` on the CSAL VM, for user deadpool. E.g. `/home/deadpool/quiz-3/fork_1.c`, `/home/deadpool/quiz-3/fork_2.c`, `/home/deadpool/quiz-3/Makefile`

For the e-learning part, create a tarball (tar.gz) that contains the aforementioned contents of folder quiz-3 and upload it.