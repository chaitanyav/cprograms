/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Implementation of dup2()
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int my_dup2(int old_fd, int new_fd) {

  if(fcntl(old_fd, F_GETFL) == -1) {
    fprintf(stderr, "%s %d\n", strerror(errno), old_fd);
  }

  if((new_fd != old_fd)) {
    close(new_fd);
  }

  new_fd = fcntl(old_fd, F_DUPFD, new_fd);

  return new_fd;
}

int main(int argc, char *argv[]) {
  int fd, new_fd, flags, new_flags;

  if((argc != 2) || (strcmp(argv[1], "--help") == 0)) {
    fprintf(stdout, "Usage: %s file_descriptor\n", argv[0]);
  } else {
    new_fd = atoi(argv[1]);
  }

  flags = O_CREAT | O_RDWR;
  fd = open("foo", flags, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "error on open\n");
    exit(EXIT_FAILURE);
  }

  new_fd = my_dup2(fd, new_fd);
  if(new_fd == -1) {
    fprintf(stderr, "error on my_dup2\n");
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
