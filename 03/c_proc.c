/*	c_proc.c
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 3
*/
#include "c_proc.h"

void get_char(char* c){
	// https://www.gnu.org/software/libc/manual/html_node/Process-Identification.html#index-getpid
	printf("Assign a character to process %d: ",getpid());
	scanf(" %c",c);
}

void sv_msg(process* p, int n){
	// https://www.gnu.org/software/libc/manual/html_node/Formatted-Output-Functions.html#index-snprintf
	snprintf(p->msg,BUFFER_SIZE,"%d) I am child process %d and my character was %c.\n",n,p->pid,p->c);
	return;
}

int create_processes(process** p_array){
	pid_t pid;
	char c;
	for(int i=0;i<N;i++){
		pid=fork();
		switch(pid){
			case -1:
				// https://www.gnu.org/software/libc/manual/html_node/Error-Messages.html#index-perror
				// https://www.gnu.org/software/libc/manual/html_node/Error-Messages.html#index-strerror
				// https://www.gnu.org/software/libc/manual/html_node/Checking-for-Errors.html#index-errno-1
				perror(strerror(errno));
				for(int j=0;i<N;j++)
					free(p_array[j]);
				free(p_array);
				return errno;
			case 0:
				p_array[i]->pid=getpid();
				get_char(&p_array[i]->c);
				sv_msg(p_array[i],i+1);
				exit(0);
			default:
				// https://www.gnu.org/software/libc/manual/html_node/Process-Completion.html#index-waitpid
				waitpid(WAIT_ANY,NULL,0); // wait for any child process to terminate
				break;
		}
	}
	return 0;
}
