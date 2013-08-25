/*
 * Author: NagaChaitanya Vellanki
 *
 * mmap and munmap example
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
  void *ptr;
  int val;

  ptr = mmap(NULL, 512 * 1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if(ptr == MAP_FAILED) {
    fprintf(stderr, "mmap failed\n");
    exit(EXIT_FAILURE);
  } else {
    val = munmap(ptr, 512 * 1024);
    if(val) {
      fprintf(stderr, "munmap failed\n");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
