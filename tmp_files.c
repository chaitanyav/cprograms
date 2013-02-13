/*
 * Author: NagaChaitanya Vellanki
 *
 * temporary files
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  char fileName[] = "/tmp/foobarXXXXXX";
  FILE *file;

  /* method 1 */
  fd = mkstemp(fileName);
  if(fd == -1) {
    fprintf(stderr, "error on mkstep\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%s is the generated filename\n", fileName);

  unlink(fileName);

  if(close(fd) == -1) {
    fprintf(stderr, "error on close\n");
    exit(EXIT_FAILURE);
  }

  /* method 2 */
  file = tmpfile();
  fclose(file);
  exit(EXIT_SUCCESS);
}
