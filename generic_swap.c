/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Generic swap function
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *a, void *b, size_t element_size) {
  char *buffer = (char *) malloc(element_size);
  memcpy(buffer, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, buffer, element_size);
}

int main(int argc, char *argv[]) {
  int a = 10;
  int b = 20;
  double c = 10.1;
  double d = 12.1;
  printf("Before swap %d %d\n", a, b);
  swap(&a, &b, sizeof(a));
  printf("After swap %d %d\n", a, b);

  printf("Before swap %f %f\n", c, d);
  swap(&c, &d, sizeof(c));
  printf("After swap %f %f", c, d);

  exit(EXIT_SUCCESS);
}
