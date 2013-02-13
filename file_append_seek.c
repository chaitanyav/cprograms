/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * open file to append and seek to begin to file and write data
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int fd;
  off_t off;

  fd = open("foo", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "error on open\n");
    exit(EXIT_FAILURE);
  }

  if(write(fd, "hello_world", 11) == -1) {
    fprintf(stderr, "error on write\n");
    exit(EXIT_FAILURE);
  }

  if(close(fd) == -1) {
    fprintf(stderr, "error on close\n");
    exit(EXIT_FAILURE);
  }


  fd = open("foo", O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "error on open\n");
    exit(EXIT_FAILURE);
  }

  if((off = lseek(fd, 0, SEEK_SET)) == -1) {
    fprintf(stderr, "error on lseek %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if(write(fd, "foo bar goo", 11) == -1) {
    fprintf(stderr, "error on write\n");
    exit(EXIT_FAILURE);
  }


  if(close(fd) == -1) {
    fprintf(stderr, "error on close\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
