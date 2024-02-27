#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int pid; /* Integer that holds the process id of the child process  */

/* Function that handles the SIGALRM */
void onalarm(int signum){
  printf("Alarm resived: %d\n", signum);
  kill(pid, SIGKILL);
}

int main(int argc, char *argv[]){

  int sec = 10, status;
  void onalarm();

  /* Process input parameters */
  if (argc > 1 && argv[1][0] == '-'){
    sec = atoi(&argv[1][1]);
    argc--, argv++;
  }

  if (argc < 2){
    printf("Usage: %s [-10] command", argv[0]);
  }

  /* Call fork to create a process  */
  pid = fork();
  if (pid == 0){

    /* Child process  */
    printf("Executing: %s\n", argv[1]);
    execvp(argv[1], &argv[1]);
    printf("execv %s failed", argv[1]);
  }
  else{

    /* Uppon reciving the signal SIGALRM call the function onalarm */
    signal(SIGALRM, onalarm);

    /* Trigger alarm after sec seconds */
    alarm(sec);

    /* Wait for child to finish.
     * If the child is killed print message.
     */

    if (wait(&status) == -1 || (status & 0xFF) != 0){
      printf("Child process killed\n");
    }
  }
}