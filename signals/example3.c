#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  int s, sig;
  if(argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("Usage %s sig-num pid\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  sig = atoi(argv[1]);
  s = kill(atol(argv[2]), sig);

  if(sig != 0) {
    if(sig == -1) {
      printf("Error on kill, %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  } else {
    if(s == 0) {
      printf("Process exists and we can send it a signal\n");
    } else {
      if(errno == EPERM) {
        printf("process exists but we don't have permission to send a signal\n");
      } else if(errno == ESRCH) {
        printf("Process does not exist\n");
      } else {
        printf("Error on kill %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
    }
  }
  exit(EXIT_SUCCESS);
}
