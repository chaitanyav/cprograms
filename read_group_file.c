
/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * ./read_group_file sys 0
 *
 *  sample output
 *  ---------------------
 *   Group name: sys
 *   Encrypted password: x
 *   Group id: 3
 *
 *   Group name: root
 *   Encrypted password: x
 *   Group id: 0
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <grp.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void print_group_info(struct group *grp) {
  if(grp != NULL) {
    printf("Group name: %s\n", grp->gr_name);
    printf("Encrypted password: %s\n", grp->gr_passwd);
    printf("Group id: %d\n", grp->gr_gid);
    for(; *(grp->gr_mem) != NULL; (grp->gr_mem)++) {
      printf("%s\n", *(grp->gr_mem));
    }
  }
}

int main(int argc, char *argv[]) {
  gid_t gid;

  if(argc < 3 || strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s group gid\n", argv[0]);
  }

  /* get info using group */
  print_group_info(getgrnam(argv[1]));

  printf("\n");

  /* get info using group id */
  gid = atoi(argv[2]);
  print_group_info(getgrgid(gid));

  exit(EXIT_SUCCESS);
}
