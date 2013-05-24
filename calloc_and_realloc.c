/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * calloc and realloc example
 *  gcc -Wall -pedantic -o calloc_and_realloc calloc_and_realloc.c
 * ------------------------------------------------------------
 * export MALLOC_TRACE=/tmp/t
 * ------------------------------------------------------------
 * ./calloc_and_realloc
 * ------------------------------------------------------------
 * mtrace ./calloc_and_realloc $MALLOC_TRACE
 *
 * Memory not freed:
 * -----------------
 *          Address     Size     Caller
 * 0x0000000000601460     0x50  at 0x40089b
 */

#include <errno.h>
#include <mcheck.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

void errExit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int *arr;
  int *newPtr;

  mtrace();
  arr = (int *) calloc(10, sizeof(int));
  if(arr == NULL) {
    errExit("error on calloc, %s\n", strerror(errno));
  }

  newPtr = realloc(arr, 20 * sizeof(int));
  if(newPtr == NULL) {
    errExit("error on realloc, %s\n", strerror(errno));
  } else {
    arr = newPtr;
  }

  muntrace();
  exit(EXIT_SUCCESS);
}
