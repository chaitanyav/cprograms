/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 * sysname -> /proc/sys/kernel/ostype
 * version -> /proc/sys/kernel/version
 * release -> /proc/sys/kernel/release
 *
 * Sample output
 * -----------------------------------------------------------------------
 *  Kernel name: Linux
 *  Hostname: ubuntu
 *  Kernel Release: 3.8.0-19-generic
 *  Kernel version: #29-Ubuntu SMP Wed Apr 17 18:16:28 UTC 2013
 *  Machine : x86_64
 *  NIS Domain name: (none)
 *
 */

#define _GNU_SOURCE
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  struct utsname utsbuf;

  if(uname(&utsbuf) != -1) {
    printf("Kernel name: %s\n", utsbuf.sysname);
    printf("Hostname: %s\n", utsbuf.nodename);
    printf("Kernel Release: %s\n", utsbuf.release);
    printf("Kernel version: %s\n", utsbuf.version);
    printf("Machine : %s\n", utsbuf.machine);
#ifdef _GNU_SOURCE
    printf("NIS Domain name: %s\n", utsbuf.domainname);
#endif

  } else {
    err_exit("Error on uname, %s\n", strerror(errno));
  }

  exit(EXIT_SUCCESS);
}
