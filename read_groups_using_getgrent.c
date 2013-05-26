/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Read entries in the groups file one at a time
 */

#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  struct group *grp;

  while((grp = getgrent()) != NULL) {
    printf("-------------------------------\n");
    printf("Group name: %s\n", grp->gr_name);
    printf("Group id: %d\n", grp->gr_gid);
    printf("Encrypted password: %s\n", grp->gr_passwd);

    for(; *(grp->gr_mem) != NULL; (grp->gr_mem)++) {
      printf("User: %s\n", *(grp->gr_mem));
    }
    printf("-------------------------------\n");
  }

  endgrent();
  exit(EXIT_SUCCESS);
}
