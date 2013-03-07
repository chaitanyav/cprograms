/*
 * Author: NagaChaitanya Vellanki
 *
 * whoami - print effective user id
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void printUsage(void) {
  fprintf(stdout, "Usage: whoami [OPTION]...\n\
      Print the user name associated with the current effective user ID.\n\n\
      -h help\n");
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  uid_t uid;
  int32_t option;
  struct passwd *pw;

  while((option = getopt(argc, argv, "h")) != -1) {
    switch(option) {
      case 'h': printUsage();
      default:  err_exit("Try 'whoami -h' for more information\n");
    }
  }

  uid = geteuid();
  if((pw = getpwuid(uid)) != NULL) {
    fprintf(stdout, "%s\n", pw->pw_name);
  } else {
    fprintf(stderr, "cannot find name for user id %u, errno is %d\n", uid, errno);
  }

  exit(EXIT_SUCCESS);
}
