/*
 * Author: NagaChaitanya Vellanki
 *
 * realloc example
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *arr, *new_arr;

  arr = calloc(50, sizeof(int));
  if(arr == NULL) {
    perror("Error on calloc");
    exit(EXIT_FAILURE);
  } else {
    new_arr = realloc(arr, sizeof(int) * 100);
    if(new_arr == NULL) {
      perror("Error on realloc");
      free(arr);
    } else {
      free(new_arr);
    }
  }

  exit(EXIT_FAILURE);
}
