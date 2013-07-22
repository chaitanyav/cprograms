/*
 * Author: NagaChaitanya Vellanki
 *
 * generates a large file with random data
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  int num_bytes;
  char *buf;

  if(argc < 2 || strcmp(argv[1], "--help")== 0) {
    printf("Usage: %s num_bytes\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  num_bytes = atoi(argv[1]);
  if(num_bytes <= 0) {
    printf("num bytes should be greater than 0\n");
      exit(EXIT_FAILURE);
  }

  fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
  if(fd != -1) {
    buf = (char *)malloc(sizeof(char) * num_bytes);
    memset(buf, 0, num_bytes);
    if(write(fd, buf, num_bytes) == -1) {
      perror("Error on write, ");
      exit(EXIT_FAILURE);
    }
  } else {
    perror("Error on open, ");
    exit(EXIT_FAILURE);
  }

  close(fd);
  free(buf);
  exit(EXIT_SUCCESS);
}
