/*
 *
 * Author: NagaChaitanya Vellanki
 *
 *
 */
#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  int fd;
  off64_t off;

  if((argc != 3) || strcmp(argv[1], "--help") == 0) {
    fprintf(stdout, "Usage: %s name offset\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = open64(argv[1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "error on open64\n");
    exit(EXIT_FAILURE);
  }

  off = atoll(argv[2]);
  if(lseek64(fd, off, SEEK_SET) == -1) {
    fprintf(stderr, "error on lseek64\n");
    exit(EXIT_FAILURE);
  }

  if(write(fd, "test", 4) == -1) {
    fprintf(stderr, "error on write\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
