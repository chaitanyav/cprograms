/*
 * Author: NagaChaitanya Vellanki
 *
 * ./read_passwd_file root 3
 *
 *  sample output
 *  -------------------------------
 *   Read /etc/passwd file
 *   Login name: root
 *   Encrypted password: x
 *   User id: 0
 *   Group id: 0
 *   User information: root
 *   Home directory: /root
 *   Login shell: /bin/bash
 *
 *   Login name: sys
 *   Encrypted password: x
 *   User id: 3
 *   Group id: 3
 *   User information: sys
 *   Home directory: /dev
 *   Login shell: /bin/sh
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pwd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void print_passwd_info(struct passwd *pwd) {
  if(pwd != NULL) {
    printf("Login name: %s\n", pwd->pw_name);
    printf("Encrypted password: %s\n", pwd->pw_passwd);
    printf("User id: %d\n", pwd->pw_uid);
    printf("Group id: %d\n", pwd->pw_gid);
    printf("User information: %s\n", pwd->pw_gecos);
    printf("Home directory: %s\n", pwd->pw_dir);
    printf("Login shell: %s\n", pwd->pw_shell);
  }
}

int main(int argc, char *argv[]) {
  uid_t uid;

  if(argc < 3 || strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s login uid\n", argv[0]);
  }

  /* get info using user login */
  print_passwd_info(getpwnam(argv[1]));

  printf("\n");

  /* get info using user id */
  uid = atoi(argv[2]);
  print_passwd_info(getpwuid(uid));

  exit(EXIT_SUCCESS);
}
