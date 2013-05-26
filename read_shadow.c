/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * sample info from /etc/shadow
 * --------------------------------------
 *  User login: dnsmasq
 *  Encrypted password: *
 *  Time of last password change 15846
 *  Minimum number of days between password changes 0
 *  Maximum number of days before password change required 99999
 *  Number of days before user is warned about password expiration 7
 *  Number of days after password expiration until account is locked -1
 *  Date when account expires -1
 *  --------------------------------------
 */

#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void print_shadow_info(struct spwd *shadow) {
  if(shadow != NULL) {
    printf("--------------------------------------\n");
    printf("User login: %s\n", shadow->sp_namp);
    printf("Encrypted password: %s\n", shadow->sp_pwdp);
    printf("Time of last password change %ld\n", shadow->sp_lstchg);
    printf("Minimum number of days between password changes %ld\n", shadow->sp_min);
    printf("Maximum number of days before password change required %ld\n", shadow->sp_max);
    printf("Number of days before user is warned about password expiration %ld\n", shadow->sp_warn);
    printf("Number of days after password expiration until account is locked %ld\n", shadow->sp_inact);
    printf("Date when account expires %ld\n", shadow->sp_expire);
    printf("--------------------------------------\n");
  }
}

int main(int argc, char *argv[]) {
  struct spwd *shadow;

  if(argc < 2 || strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s login\n", argv[0]);
  }

  print_shadow_info(getspnam(argv[1]));

  while((shadow = getspent()) != NULL) {
    print_shadow_info(shadow);
  }

  endspent();

  exit(EXIT_SUCCESS);
}
