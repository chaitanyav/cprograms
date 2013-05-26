/*
 * Author: NagaChaitanya Vellanki
 *
 * Refer to Listing 8-2 of LPI book
 *
 * Authenticate user against the /etc/shadow
 * gcc -Wall -pedantic -o check_user_password check_user_password.c -lcrypt
 *
 * sudo ./check_user_password
 * sample output
 * --------------------------------------
 * Enter user login:
 * matti-nillu
 * Enter password:
 * successfully authenticated user matti-nillu
 *
 * ---------------------------------------
 * sudo ./check_user_password
 * Enter user login:
 * root
 * Enter password:
 * successfully authenticated user root
 *
 */

#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <errno.h>
#include <pwd.h>
#include <shadow.h>
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
  char *login, *password, *encrypted_password, *temp;
  struct passwd *pwd;
  struct spwd *shadow;
  long login_max;
  size_t len;

  login_max = sysconf(_SC_LOGIN_NAME_MAX);
    if(login_max == -1) {
      login_max = 256;
    }

  login = (char *)malloc(login_max);
  if(login == NULL) {
    err_exit("error on malloc, %s\n", strerror(errno));
  }

  fprintf(stdout, "Enter user login:\n");
  if(fgets(login, login_max, stdin) == NULL) {
    err_exit("eof reached, %s\n", strerror(errno));
  }

  len = strlen(login);
  if(login[len - 1] == '\n') {
    login[len - 1] = '\0';
  }

  pwd = getpwnam(login);
  if(pwd == NULL) {
    err_exit("could not read /etc/passwd, %s\n", strerror(errno));
  }

  shadow = getspnam(login);
  if(shadow == NULL) {
    err_exit("could not read /etc/shadow, %s\n", strerror(errno));
  } else {
    pwd->pw_passwd = shadow->sp_pwdp;
  }

  password = getpass("Enter password:");
  encrypted_password = crypt(password, pwd->pw_passwd);
  for(temp = password; *temp != '\0'; temp++) {
    *temp = '\0';
  }

  if(encrypted_password == NULL) {
    err_exit("error on crypt, %s\n", strerror(errno));
  }

  if(strcmp(pwd->pw_passwd, encrypted_password) == 0) {
    fprintf(stdout, "successfully authenticated user %s\n", pwd->pw_name);
  } else {
    fprintf(stdout, "incorrect password for %s\n", pwd->pw_name);
  }

  exit(EXIT_SUCCESS);
}

