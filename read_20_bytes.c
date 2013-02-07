#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUF_SIZE 20

int main(int argc, char *argv[]) {
  char buf[BUF_SIZE + 1];
  ssize_t numRead;

  if((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) == -1) {
    printf("could not read from stdin\n");
    exit(EXIT_FAILURE);
  }

  buf[numRead] = '\0';
  printf("input was %s\n", buf);
  exit(EXIT_SUCCESS);
}
