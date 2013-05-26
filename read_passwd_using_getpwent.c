/*
 *
 * Author: NagaChaitanya Vellanki
 *
 *
 * Read entries in the passwd one at a time using getpwent
 */

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  struct passwd *pwd;

  while((pwd = getpwent()) != NULL) {
    printf("-------------------------------\n");
    printf("User login: %s\n", pwd->pw_name);
    printf("Encrypted password: %s\n", pwd->pw_passwd);
    printf("User id: %d\n", pwd->pw_uid);
    printf("Group id: %d\n", pwd->pw_gid);
    printf("User information: %s\n", pwd->pw_gecos);
    printf("Home directory: %s\n", pwd->pw_dir);
    printf("Login Shell: %s\n", pwd->pw_shell);
    printf("-------------------------------\n");
  }

  endpwent();

  exit(EXIT_SUCCESS);
}
