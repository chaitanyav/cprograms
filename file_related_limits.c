/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * file limits using fpathconf()
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void fpathconf_print(const char *msg, int fd, int name) {
  long lim = 0;
  errno = 0;

  lim = fpathconf(fd, name);
  if(lim != -1) {
    printf("%s value is %ld\n", msg, lim);
  } else {
    if(errno == 0) {
      printf("fpathconf(STDIN_FILENO, %s)succeeded and %s value indeterminate\n", msg, msg);
    } else {
      err_exit("Erron on fpathconf(STDIN_FILENO, %s), %s\n", msg, strerror(errno));
    }
  }
}

int main(int argc, char *argv[]) {
  fpathconf_print("_PC_NAME_MAX", STDIN_FILENO, _PC_NAME_MAX);
  fpathconf_print("_PC_PATH_MAX", STDIN_FILENO, _PC_PATH_MAX);
  fpathconf_print("__PC_PIPE_BUF", STDIN_FILENO, _PC_PIPE_BUF);

  exit(EXIT_SUCCESS);
}
