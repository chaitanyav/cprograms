#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
  for(int i = 0; i < 32; i++) {
    printf("%d signal is %s\n", i, strerror(i));
  }
  exit(EXIT_SUCCESS);
}
