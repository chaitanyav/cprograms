/*
 * Author: NagaChaitanya Vellanki
 *
 * posix memalign example
 */

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *buf;
  int val;

  val = posix_memalign((void *)&buf, 256, 1000);

  if(val) {
    printf("Error on posix_memalign: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    free(buf);
  }

  exit(EXIT_SUCCESS);
}
