#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv){

  int t = atoi(argv[1]);
  int handler();

  signal(SIGINT, SIG_IGN);

  printf("sleeping for: %d sec\n", t);

  sleep(t);
}