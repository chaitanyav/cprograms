/*
 * Author: NagaChaitanya Vellanki
 *
 * gcc -Wall -o program_name program_name.c -D_GNU_SOURCE
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("%s\n", program_invocation_name);
  printf("%s\n", program_invocation_short_name);
  exit(EXIT_SUCCESS);
}
