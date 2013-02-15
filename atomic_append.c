/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * $ atomic_append f1 1000000 & atomic_append f1 1000000
 * $ atomic_append f2 1000000 x & atomic_append f2 1000000 x
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef enum {false, true} bool;

int main(int argc, char *argv[]) {
  int fd, flags;
  bool append;
  long num_bytes, i;

  if((argc < 3) || (strcmp(argv[1], "--help") == 0)) {
    fprintf(stdout, "Usage: atomic_append filename num-bytes [x]\n");
    exit(EXIT_FAILURE);
  }

  num_bytes = strtol(argv[2], NULL, 10);

  if(argc == 3) {
    append = true;
  }

  if((argc == 4) ) {
    if(strcmp(argv[3], "x") == 0){
      append = false;
    } else {
      exit(EXIT_FAILURE);
    }
  }

  flags = O_CREAT | O_WRONLY;
  if(append) {
    flags |= O_APPEND;
  }

  fd = open(argv[1], flags, S_IRUSR | S_IWUSR);
  if(fd == -1) {
    fprintf(stderr, "error on open\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0; i < num_bytes; i++) {
    if(!append) {
      if(lseek(fd, 0, SEEK_END) == -1) {
        fprintf(stderr, "error on seek\n");
        exit(EXIT_FAILURE);
      }
    }

    if(write(fd, "1", 1) == -1) {
      fprintf(stderr, "error on write\n");
      exit(EXIT_FAILURE);
    }
  }

  if(close(fd) == -1) {
    fprintf(stderr, "error on close\n");
    exit(EXIT_FAILURE);

  }
  exit(EXIT_SUCCESS);
}
