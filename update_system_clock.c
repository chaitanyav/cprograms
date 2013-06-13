/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * adjtime() can also be used
 */

#define _BSD_SOURCE
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  struct timeval tv;

  if(gettimeofday(&tv, NULL) == -1) {
    err_exit("Errron on gettimeoftheday %s\n", strerror(errno));
  }

  if(settimeofday(&tv, NULL) == -1) {
    err_exit("Errron on settimeoftheday %s\n", strerror(errno));
  }

  exit(EXIT_SUCCESS);
}
