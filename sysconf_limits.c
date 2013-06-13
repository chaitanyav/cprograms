/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * ./sysconf_limits
 *
 * Sample output
 * ---------------------------------------------------------------------------
 * _SC_ARG_MAX value is 131072
 * _SC_OPEN_MAX value is 1024
 * _SC_NGROUPS_MAX value is 65536
 * _SC_PAGESIZE value is 4096
 * _SC_RTSIG_MAX value is 32
 * _SC_LOGIN_NAME_MAX value is 256
 *
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

void sysconf_print(const char *msg, int name) {
  long lim = 0;
  errno = 0;

  lim = sysconf(name);
  if(lim != -1) {
    printf("%s value is %ld\n", msg, lim);
  } else {
    if(errno == 0) {
      printf("sysconf(%s)succeeded and %s value indeterminate\n", msg, msg);
    } else {
      err_exit("Erron on sysconf(%s), %s\n", msg, strerror(errno));
    }
  }
}

int main(int argc, char *argv[]) {
  sysconf_print("_SC_ARG_MAX", _SC_ARG_MAX);
  sysconf_print("_SC_OPEN_MAX", _SC_OPEN_MAX);
  sysconf_print("_SC_NGROUPS_MAX", _SC_NGROUPS_MAX);
  sysconf_print("_SC_PAGESIZE", _SC_PAGESIZE);
  sysconf_print("_SC_RTSIG_MAX", _SC_RTSIG_MAX);
  sysconf_print("_SC_LOGIN_NAME_MAX", _SC_LOGIN_NAME_MAX);

  exit(EXIT_SUCCESS);
}
