#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

#define BUFSIZE 100

void child(int i, int *pd) {
  
  char buf[BUFSIZE];
  int wr = 0;
  
  close(pd[0]); /* Close the reading end of the pipe */
  sprintf(buf, "Ηello from child %2d (pid=%5d)\n", i, getpid());
  wr = write(pd[1], buf, strlen(buf)+1);
  close(pd[1]);
  
}

int main(int argc, char *argv[]) {

  int N = atoi(argv[1]);
  printf("Creating %d children\n", N);
  
  int pd[2];  
  int i, n;
  char buf[BUFSIZE];
  int wr = 0;
  
  if ( pipe(pd) < 0 ){ printf("can’t open pipe");}

  for (i=1; i<=N; i++)
    if ( fork() == 0 ) { /* Create a child process */
      child(i, pd);
      exit(0);
    }

  close(pd[1]); /* Close the writing end of the pipe */

  printf("FATHER: I receiνed from children:\n\n");
  while ( (n=read(pd[0], buf, BUFSIZE)) > 0 ){
    wr = write(1, buf, n); /* 1=stdout */
  }
  close(pd[0]);
}


