/*
 * Author: NagaChaitanya Vellanki
 *
 * Program to verify that duplicated file descriptors share a file offset
 * value and open file status flags
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  int fd1, fd2, flags;
  char *file = "foo";
  off_t off1, off2;

  fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if(fd1 == -1) {
    fprintf(stderr, "error on open\n");
    exit(EXIT_FAILURE);
  } else {
    fd2 = dup(fd1);
    fprintf(stdout, "fd1 is %d and fd2 is %d\n", fd1, fd2);

    if(write(fd1, "hello_world", 11) == -1) {
      fprintf(stderr, "error on write\n");
      exit(EXIT_FAILURE);
    }

    if((off1 = lseek(fd1, 0, SEEK_CUR)) != -1) {
      fprintf(stdout, "%ld is offset for %d\n", off1, fd1);
    }

    if((off2 = lseek(fd2, 0, SEEK_CUR)) != -1) {
      fprintf(stdout, "%ld is offset for %d\n", off2, fd2);
    }

    if((flags = fcntl(fd1, F_GETFL) != -1)) {
      fprintf(stdout, "%d are flags for %d\n", flags, fd1);
    }

    if((flags = fcntl(fd2, F_GETFL) != -1)) {
      fprintf(stdout, "%d are flags for %d\n", flags, fd2);
    }

    if(close(fd1) == -1) {
      fprintf(stderr, "error on close\n");
      exit(EXIT_FAILURE);
    }

    if(close(fd2) == -1) {
      fprintf(stderr, "error on close\n");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
