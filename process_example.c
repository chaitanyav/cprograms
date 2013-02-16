/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * To get Max process id
 * cat /proc/sys/kernel/pid_max
 * 32768
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  fprintf(stdout, "Process id is %d\n", getpid());
  fprintf(stdout, "Parent Process id is %d\n", getppid());
  exit(EXIT_SUCCESS);
}
