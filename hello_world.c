/*
 * Author: NagaChaitanya Vellanki
 *
 * generating assembly for a c file
 *
 * gcc -S -c hello_world.c
 *
 * will generate a hello_world.s
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("Hello World!\n");
  exit(EXIT_SUCCESS);
}
