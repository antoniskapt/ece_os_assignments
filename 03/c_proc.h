/*	c_proc.h
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 3
*/
#ifndef C_PROC_H
#define C_PROC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#define N 4
#define BUFFER_SIZE 512

/*	Structure that holds the global id of a process in __pid__, its character in __c__ and its message in __msg__. */
typedef struct{
	// https://www.gnu.org/software/libc/manual/html_node/Process-Identification.html#index-pid_005ft
	pid_t pid;
	char c;
	char msg[BUFFER_SIZE];
} process;

/*	Read a character from stdin and store it in __c__. */
void get_char(char* c);

/*	Stores the message of the calling process to p->__msg__. */
void sv_msg(process* p, int n);

/*	Create N processes and for every child process call __sv_msg__(__p_array__[i]). */
int create_processes(process** p_array);

#endif
