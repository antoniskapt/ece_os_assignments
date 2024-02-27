#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define MAXLINE 512

int main(int argc, char **argv){

  int n, fd[2];
  pid_t pid;
  char line[MAXLINE];
  int wr = 0;

  if (pipe(fd) < 0) { /* Failde to create the pipe */
    perror("creating pipe");
    exit(1);
  }
  if ((pid = fork()) < 0){
    /* Failed to create child process */
    perror("cannot fork");
    exit(1);
  }
  else if (pid > 0) /* Parent process */
    {
      close(fd[0]); /* Close reading end of pipe */
      wr = write(fd[1], "message through pipe\n", 21);  /* Write to the pipe */
      close(fd[1]);
    }
  else
    { /* Child process */
      close(fd[1]); /* Close the writing end of the pipe */
      n = read(fd[0], line, MAXLINE); /* Read from the pipe */
      wr = write(STDOUT_FILENO, line, n); close(fd[0]);
    }
  exit(0);
}
