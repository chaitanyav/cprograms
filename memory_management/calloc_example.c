/*
 * Author: NagaChaitanya Vellanki
 *
 * calloc example
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *arr;
  arr = calloc(50, sizeof(int));

  if(arr == NULL) {
    perror("Error on calloc");
    exit(EXIT_FAILURE);
  } else {
    free(arr);
  }

  exit(EXIT_SUCCESS);
}

