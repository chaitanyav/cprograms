/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Get File system uid, gid
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/fsuid.h>

int main(int argc, char *argv[]) {
  printf("File system UID: %d\n", setfsuid(-1));
  printf("File system GID: %d\n", setfsgid(-1));
  exit(EXIT_SUCCESS);
}
