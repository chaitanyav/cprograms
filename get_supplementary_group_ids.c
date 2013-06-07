/*
 * Author: NagaChaitanya Vellanki
 *
 *
 */

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  gid_t grouplist[NGROUPS_MAX + 1];
  int num_groups = 0, i = 0;

  if((num_groups = getgroups(NGROUPS_MAX, grouplist)) == -1) {
    err_exit("Error on getgroups %s\n", strerror(errno));
  }

  printf("This process is a member of the following groups:\n");
  for(; i < num_groups; i++) {
    printf("%d\n", grouplist[i]);
  }

  exit(EXIT_SUCCESS);
}
