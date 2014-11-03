#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int sig) {
  printf("Received interrupt signal\n");
}

int main(int argc, char *argv[]) {
  int j;

  if(signal(SIGINT, sig_handler) == SIG_ERR) {
    printf("Error on signal\n");
    exit(EXIT_FAILURE);
  }

  for(j = 0; ; j++) {
    printf("%d\n", j);
    sleep(3);
  }
  return 0;
}
