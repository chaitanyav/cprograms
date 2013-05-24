/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 * mtrace and muntrace example
 *
 * Running the program and sample output:
 *
 * gcc -Wall -pedantic -o mtrace_and_muntrace mtrace_and_muntrace.c
 * ------------------------------------------------------------
 * export MALLOC_TRACE=/tmp/t
 * ------------------------------------------------------------
 * ./mtrace_and_muntrace
 * ------------------------------------------------------------
 * mtrace ./mtrace_and_muntrace $MALLOC_TRACE

 * Memory not freed:
 * -----------------
 *           Address     Size     Caller
 * 0x0000000000601460     0x64  at 0x4005e3
 * 0x00000000006014d0     0x64  at 0x4005e3
 * 0x0000000000601540     0x64  at 0x4005e3
 * 0x00000000006015b0     0x64  at 0x4005e3
 * 0x0000000000601620     0x64  at 0x4005e3
 * 0x0000000000601690     0x64  at 0x4005e3
 * 0x0000000000601700     0x64  at 0x4005e3
 * 0x0000000000601770     0x64  at 0x4005e3
 * 0x00000000006017e0     0x64  at 0x4005e3
 * 0x0000000000601850     0x64  at 0x4005e3
 * ------------------------------------------
 */

#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  int i;

  mtrace();
  for(i = 0; i < 10; i++) {
    malloc(100);
  }

  muntrace();

  malloc(4);
  exit(EXIT_SUCCESS);
}
