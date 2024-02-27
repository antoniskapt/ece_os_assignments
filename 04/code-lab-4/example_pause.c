#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void catcher( int sig ) {
  printf( "Signal catcher called for signal %d\n", sig );
}

void timestamp( char *str ) {
  time_t t;

  time(&t);
  printf( "The time %s is %s\n", str, ctime(&t) );
}

int main( int argc, char *argv[] )  {

  int t = atoi(argv[1]);

  
  signal(SIGALRM, catcher);


  alarm( t );

  timestamp( "before pause" );
  pause();
  timestamp( "after pause" );

  return( 0 );
}

