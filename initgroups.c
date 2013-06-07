/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Implementation of initgroups using setgroups, functions to read /etc/passwd file
 */

#define _BSD_SOURCE

#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_initgroups(const char *user, gid_t group) {
  struct passwd *pwd;
  gid_t *grouplist, read_grouplist[NGROUPS_MAX + 1];
  int num_groups = 0, i = 0;

  pwd = getpwnam(user);

  if(pwd != NULL) {
    num_groups = getgroups(NGROUPS_MAX, read_grouplist);
    grouplist = malloc((num_groups + 1) * sizeof(gid_t));

    if(grouplist != NULL) {

      for(; i < num_groups; i++) {
        grouplist[i] = read_grouplist[i];
      }

      grouplist[i] = group;

      if(setgroups(num_groups + 1, grouplist) != -1) {
        return 0;
      }
  }
  }

  return -1;
}


int main(int argc, char *argv[]) {
  gid_t groupslist[NGROUPS_MAX + 1], group = 2000;
  int i = 0, num_groups = 0;
  int flag = 0;

  printf("Adding a new group id to list of supplemental group ids, output(0 for success, -1 for error): %d\n", my_initgroups("root", group));

  printf("Retrieving the list of supplemental group ids for this process to check for the new group id\n");
  num_groups = getgroups(NGROUPS_MAX, groupslist);
  for(; i < num_groups; i++) {
    if(group == groupslist[i]) {
      flag = 1;
      break;
    }
  }

  if(flag) {
   printf("SUCCESS: Adding group id %d to supplemental group ids\n", group);
  } else {
   printf("FAILURE: Adding group id %d to supplemental group ids\n", group);
  }

  exit(EXIT_SUCCESS);
}
