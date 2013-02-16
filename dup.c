/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Implementation of dup()
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int my_dup(int fd) {
  int new_fd;
  new_fd = fcntl(fd, F_DUPFD);
  return new_fd;
}

int main(int argc, char *argv[]) {
  int fd, new_fd, flags, new_flags;

  flags = O_CREAT | O_RDWR;
  fd = open("foo", flags, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "error on open\n");
    exit(EXIT_FAILURE);
  }

  new_fd = my_dup(fd);
  if(new_fd == -1) {
    fprintf(stderr, "error on my_dup\n");
    exit(EXIT_FAILURE);
  }

  new_flags = fcntl(new_fd, F_GETFL);
  if(new_flags == -1) {
    fprintf(stderr, "error on fcntl\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "new fd: %d, old fd: %d, new flags: %d, old flags: %d\n ", new_fd, fd, new_flags, flags);
  if((new_flags & O_ACCMODE) == O_RDWR) {
    fprintf(stdout, "new fd also has same access flags\n");
  }

  if(close(fd) == -1) {
    fprintf(stderr, "error on close\n");
    exit(EXIT_FAILURE);
  }

  if(close(new_fd) == -1) {
    fprintf(stderr, "error on close\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
