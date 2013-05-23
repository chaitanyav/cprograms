/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Sample output:
*   0x601000 before malloc calls
*   program break after malloc call 0x622000
*   program break after malloc call 0x622000
*   program break after malloc call 0x622000
*   Address of i: 0x601010
*   Address of j: 0x601030
*   Address of k: 0x601060
*   Difference between i, j addresses: 32
*   Difference between j, k addresses 48
*   Difference between address i, sbrk(0): 135152
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *i, *j, *k;

  printf("%p before malloc calls\n", sbrk(0));
  i  = (int *) malloc(sizeof(int));
  printf("program break after malloc call %p\n", sbrk(0));
  j = (int *) malloc(10 * sizeof(int));
  printf("program break after malloc call %p\n", sbrk(0));
  k = (int *) malloc(sizeof(int));
  printf("program break after malloc call %p\n", sbrk(0));
  printf("Address of i: %p\nAddress of j: %p\nAddress of k: %p\nDifference between i, j addresses: %ld\nDifference between j, k addresses: %ld\nDifference between address i, sbrk(0): %ld\n", (void *)i, (void *)j, (void *)k, (char *) j - (char *) i, (char *)k - (char *)j, (char *) sbrk(0) - (char *)i);

  free(i);
  free(j);
  free(k);
  exit(EXIT_SUCCESS);
}
