/*	mysigcatchmodified.c
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 4
*
*	References:
*	- https://www.gnu.org/software/libc/manual/html_node/Sigaction-Function-Example.html
*	- https://pubs.opengroup.org/onlinepubs/007904875/functions/sigaction.html
*	- https://www.gnu.org/software/libc/manual/html_node/Signal-Sets.html#index-sigemptyset
*	- https://pubs.opengroup.org/onlinepubs/9699919799/functions/sigemptyset.html
*/
#include <stdio.h>
#include <signal.h>

#define sig SIGINT

volatile sig_atomic_t ret=1;
volatile sig_atomic_t cnt=0;


void catch_signal(int signo);

int main(void){
	struct sigaction sa;
	sa.sa_handler=catch_signal;
	sa.sa_flags=0; // no special flags are set
	// This function initializes the signal set to exclude all of the defined signals:
	sigemptyset(&sa.sa_mask);

	if(sigaction(sig,&sa,NULL)==-1){
		printf("Error in sigaction\n");
		return -1;
	}

	while(ret){}
	return 0;
}

void catch_signal(int signo){
	printf(" Caught signal %d\n",signo);
	++cnt;
	if(cnt==2){
		struct sigaction sa;
		sa.sa_handler=SIG_DFL; // set to default signal handling
		sa.sa_flags=0;
		sigemptyset(&sa.sa_mask);

		if(sigaction(signo, &sa, NULL) == -1)
			printf("Error in sigaction\n");
	}
}