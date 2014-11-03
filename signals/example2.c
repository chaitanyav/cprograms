#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_handler(int sig) {
  static int count = 0;
  if(sig == SIGINT) {
    count++;
    printf("Caught SIGINT (%d)\n", count);
    return;
  }

  printf("Caught SIGQUIT\n");
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

  if(signal(SIGINT, sig_handler) == SIG_ERR) {
    printf("Error on signal\n");
    exit(EXIT_FAILURE);
  }
  if(signal(SIGQUIT, sig_handler) == SIG_ERR) {
    printf("Error on signal\n");
    exit(EXIT_FAILURE);
  }

  for(;;) {
    pause();
  }
  exit(EXIT_SUCCESS);
}
