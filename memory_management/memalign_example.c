/*
 * Author: NagaChaitanya Vellanki
 *
 *  memalign example
 */

#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *buf;

  buf = memalign(getpagesize(), sizeof(char) * 1000);
  if(buf == NULL) {
    printf("Error on memalign: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    printf("Address of buf %p\n", buf);
    free(buf);
  }

  exit(EXIT_SUCCESS);
}
