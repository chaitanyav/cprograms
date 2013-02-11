/*
 * Author: NagaChaitanya Vellanki
 *
 * prints effective user_id, real user_id, group_id, initial working
 * directory and login shell
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  uid_t uid;
  struct passwd *pw;


  /* return the effective user id of the calling process */
  uid = geteuid();
  printf("effective user id is %u\n", uid);

  /* return the real user id of the calling process */
  uid = getuid();
  printf("real user id is %u\n", uid);

  if((pw = getpwuid(uid)) != NULL) {
    printf("User's login name is %s\n", pw->pw_name);
    printf("User's numerical user id is  %u\n", pw->pw_uid);
    printf("User's numerical group id is  %u\n", pw->pw_gid);
    printf("User's initial working directory is  %s\n", pw->pw_dir);
    printf("User's shell is  %s\n", pw->pw_shell);
  } else {
    printf("errno is %d\n", errno);
  }

  exit(EXIT_SUCCESS);
}
