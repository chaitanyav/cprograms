/*
 * Author: NagaChaitanya Vellanki
 *
 * malloc_usable_size() and malloc_trim() examples
 */
#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *buf;

  buf = malloc(sizeof(char) * 50);
  if(buf == NULL) {
    fprintf(stderr, "Error on malloc: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    printf("Allocated memory %zu\n", malloc_usable_size(buf));
    free(buf);
    if(malloc_trim(0)) {
      printf("Memory released\n");
    } else {
      printf("Memory was not released\n");
    }
  }
  exit(EXIT_SUCCESS);
}
