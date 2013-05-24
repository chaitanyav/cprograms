/*
 *
 * Author: NagaChaitanya Vellanki
 *
 *
 * See Listing 7-1, chapter 4 of LPI book
 *
 *  sample output:
 *
 *   ./free_and_sbrk 1000 10240 1 1 1000
 *   Initial program break is at 0x602000
 *   Allocating 1000 * 10240 bytes
 *   Program break is now at 0xfca000
 *   Freeing blocks from 1 to 1000 in steps of 1
 *   After freeing program break is at 0x623000
 *   ------------------------------------------------------------
 *   ./free_and_sbrk 1000 10240 2 1 1000
 *   Initial program break is at 0x602000
 *   Allocating 1000 * 10240 bytes
 *   Program break is now at 0xfca000
 *   Freeing blocks from 1 to 1000 in steps of 2
 *   After freeing program break is at 0xfca000
 *   ------------------------------------------------------------
 *   ./free_and_sbrk 1000 10240 1 1 999
 *   Initial program break is at 0x602000
 *   Allocating 1000 * 10240 bytes
 *   Program break is now at 0xfca000
 *   Freeing blocks from 1 to 999 in steps of 1
 *   After freeing program break is at 0xfca000
 *   ------------------------------------------------------------
 *   ./free_and_sbrk 1000 10240 1 500 999
 *   Initial program break is at 0x602000
 *   Allocating 1000 * 10240 bytes
 *   Program break is now at 0xfca000
 *   Freeing blocks from 500 to 999 in steps of 1
 *   After freeing program break is at 0xfca000
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALLOCS 1000000

void errExit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  char *ptr[MAX_ALLOCS];
  int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

  if(argc < 3 || strcmp(argv[1], "--help") == 0) {
    errExit("Usage: %s num-allocs block-size [step [min [max]]]\n", argv[0]);
  }

  numAllocs = atoi(argv[1]);
  blockSize = atoi(argv[2]);
  freeStep = (argc > 3) ? atoi(argv[3]) : 1;
  freeMin = (argc > 4) ? atoi(argv[4]) : 1;
  freeMax = (argc > 5) ? atoi(argv[5]) : numAllocs;

  if(freeMax > numAllocs) {
    errExit("cannot free more than %d\n", numAllocs);
  }

  printf("Initial program break is at %p\n", sbrk(0));
  printf("Allocating %d * %d bytes\n", numAllocs, blockSize);

  for(j = 0; j < numAllocs; j++) {
    ptr[j] = malloc(blockSize);
    if(ptr[j] == NULL) {
      errExit("error on malloc,%s\n", strerror(errno));
    }
  }

  printf("Program break is now at %p\n", sbrk(0));

  printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);
  for(j = freeMin - 1; j < freeMax; j += freeStep) {
    free(ptr[j]);
  }

  printf("After freeing program break is at %p\n", sbrk(0));

  exit(EXIT_SUCCESS);
}
