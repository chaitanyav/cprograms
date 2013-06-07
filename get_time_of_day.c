/*
 * Author: NagaChaitanya Vellanki
 *
 *
 */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void err_exit(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
  struct timeval tv;
  struct timezone tz;
  time_t timep;

  if(gettimeofday(&tv, &tz) == -1) {
    err_exit("Erron on gettimeofday %s\n", strerror(errno));
  }

  printf("Seconds since 00:00:00 1 Jan 1970 UTC: %ld\n", tv.tv_sec);
  printf("Microseconds: %ld\n", tv.tv_usec);

  if(time(&timep) == -1) {
    err_exit("Erron on time %s\n", strerror(errno));
  }

  printf("Seconds since 00:00:00 1 Jan 1970 UTC: %ld\n", timep);
  printf("Seconds since 00:00:00 1 Jan 1970 UTC: %ld\n", time(NULL));

  exit(EXIT_SUCCESS);
}
