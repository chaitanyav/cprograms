/*
 * Author: NagaChaitanya Vellanki
 *
 * mmap using a fd
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  void *ptr;
  int val;

  fd = open("/dev/zero", O_RDWR);
  if(fd != -1) {
    ptr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(ptr == MAP_FAILED) {
      fprintf(stderr, "Error on mmap: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    } else {
      printf("Address of ananonymous memory mapping %p\n", ptr);
      val = munmap(ptr, getpagesize());
      if(val == -1) {
        fprintf(stderr, "Error on munmap: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      close(fd);
    }
  } else {
    fprintf(stderr, "Error on open: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
