/*
 * Author: NagaChaitanya Vellanki
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd;

  if(close(STDIN_FILENO) == -1) {
    printf("could not close stdin file descriptor\n");
    exit(EXIT_FAILURE);
  }

  /* open uses lowest available file descriptor */
  /* in this case 0 since we have closed stdin */
  fd = open("contract.txt", O_RDONLY);
  if(fd == -1) {
    printf("could not open file\n");
    exit(EXIT_FAILURE);
  }

  printf("%d is value of file descriptor\n", fd);
  exit(EXIT_SUCCESS);
}
