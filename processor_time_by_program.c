/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 * processor time taken by the program
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void do_something() {
  int i = 0;
  for(;i < 10000000; i++) {
  }
}

int main(int argc, char *argv[]) {
  clock_t t;
  t = clock();
  do_something();
  t = clock() - t;
  printf("Number of ticks per second %ld\n", CLOCKS_PER_SEC);
  printf("Number of ticks taken by program %ld and %f seconds\n", t, ((float) t) / CLOCKS_PER_SEC);
  exit(EXIT_SUCCESS);
}
