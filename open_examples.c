#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

void closeFd(int fd) {
  if(close(fd)) {
    printf("error closing file descriptor\n");
    exit(EXIT_FAILURE);
  }
}
int main(int argc, char *argv[]) {
  int fd;
  fd = open("contract.txt", O_RDONLY);
  if(fd == -1) {
    printf("error opening file\n");
    exit(EXIT_FAILURE);
  }

  closeFd(fd);

  fd = open("contract1.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    printf("error opening file\n");
    exit(EXIT_FAILURE);
  }

  closeFd(fd);

  fd = open("w.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);

  if(fd ==-1) {
    printf("error opening file\n");
    exit(EXIT_FAILURE);
  }
  closeFd(fd);

  exit(EXIT_SUCCESS);
}

