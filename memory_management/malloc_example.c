/*
 * Author: NagaChaitanya Vellanki
 *
 * malloc example
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *name;
  name = malloc(sizeof(char) * 512);
  if(name == NULL) {
    perror("Error on malloc");
    exit(EXIT_FAILURE);
  } else {
    free(name);
  }

  exit(EXIT_SUCCESS);
}
