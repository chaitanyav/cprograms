#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  int num_sigs, sig, j;
  pid_t pid;

  if(argc < 4 || strcmp(argv[1], "--help") == 0) {
    printf("Usage %s pid num-sigs sig-num [sig-num-2]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  pid = atol(argv[1]);
  num_sigs = atoi(argv[2]);
  sig = atoi(argv[3]);

  printf("%s: sending signal %d to process %ld %d times\n", argv[0], sig, (long)pid, num_sigs);

  for(j = 0; j < num_sigs; j++) {
    if(kill(pid, sig) == -1) {
      printf("Error on kill, %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if(argc > 4) {
    if(kill(pid, atoi(argv[4])) == -1) {
      printf("Error on kill, %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  printf("%s: exiting\n", argv[0]);
  exit(EXIT_SUCCESS);
}
