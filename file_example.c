/*
 * Author: NagaChaitanya Vellanki
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1, fd2, fd3;
  char *file= "foo";
  fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  fd2 = dup(fd1);
  fd3 = open(file, O_RDWR);
  write(fd1, "Hello,", 6);
  write(fd2, "world", 6);
  lseek(fd2, 0, SEEK_SET);
  write(fd1, "HELLO,", 6);
  write(fd3, "Gidday", 6);

  exit(EXIT_SUCCESS);
}
