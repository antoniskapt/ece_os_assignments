/*	mysigcatch.c
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 4
*/
#include <stdio.h>
#include <signal.h>

#define sig SIGINT

// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/signal.h.html
volatile sig_atomic_t ret=1;

// Catches the SIGINT signal.
void catch_SIGINT(int signo);

int main(void){

	if(signal(sig,catch_SIGINT)==SIG_ERR){
		printf("Error in signal\n");
		return -1;
	}

	// Once SIGINT is caught, ret is set to 0
	// and the while loop terminates.
	while(ret){}
	return 0;
}

void catch_SIGINT(int signo){
	if(signo==sig){
		printf(" SIGINT signal caught!\n");
		ret=0;
	}
}