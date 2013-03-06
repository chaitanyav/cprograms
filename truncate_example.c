/*
 *
 *Author: NagaChaitanya Vellanki
 *
 *
 * truncate example
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>


int main(int argc, char *argv[]) {
  int fd;
  off_t offset = 0;
  char file_name[] = "/home/matti-nillu/cprograms/foo";

  fd = open("foo", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "Error on open\n");
    exit(EXIT_FAILURE);
  }

  if(write(fd, "foobar", 6) == -1) {
    fprintf(stderr, "Error on write\n");
    exit(EXIT_FAILURE);
  }

  if(truncate(file_name, offset) == -1) {
    fprintf(stderr, "Error on truncate\n");
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if(write(fd, "foobargoo", 9) == -1) {
    fprintf(stderr, "Error on write\n");
    exit(EXIT_FAILURE);
  }

  if(ftruncate(fd, offset) == -1) {
    fprintf(stderr, "Error on ftruncate\n");
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if(close(fd) == -1) {
    fprintf(stderr, "Error on close\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
