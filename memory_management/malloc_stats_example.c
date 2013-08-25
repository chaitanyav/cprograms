/*
 * Author: NagaChaitanya Vellanki
 *
 * malloc stats example
 *
 */

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *buf;
  struct mallinfo m;

  buf = malloc(sizeof(char) * 50);
  if(buf != NULL) {
    malloc_stats();
    printf("\nmalloc info using mallinfo\n");
    printf("Arena: %d\n", m.arena);
    printf("Number of free chunks: %d\n", m.ordblks);
    printf("Number of fast bins: %d\n", m.smblks);
    printf("Number of Anonymous mappings: %d\n", m.hblks);
    printf("Size of Anonymous mappings: %d\n", m.hblkhd);
    printf("Maximum total allocated size: %d\n", m.usmblks);
    printf("Size of Available fast bins: %d\n", m.fsmblks);
    printf("Size of total allocated space: %d\n", m.uordblks);
    printf("Size of available chunks: %d\n", m.fordblks);
    printf("Size of trimmable space: %d\n", m.keepcost);
    free(buf);
  }
  exit(EXIT_SUCCESS);
}
