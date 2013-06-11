/*
 * Author: NagaChaitanya Vellanki
 *
 * strptime example listing 10-3 of LPI book
 */

#define _XOPEN_SOURCE
#define BUF_SIZE 1000

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char *my_strftime(const char *format, struct tm *tmp) {
  static char buf[BUF_SIZE];
  size_t s;

  if(tmp == NULL) {
    return NULL;
  }

  s = strftime(buf, BUF_SIZE, (format != NULL) ? format: "%A %B %d %I:%M:%S %p %Y %Z", tmp);
  return (s == 0) ? NULL : buf;
}

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  struct tm tm;

  if(argc < 3 || strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s input-date-time format-string [out-format]\n", argv[0]);
  }

  memset(&tm, 0, sizeof(struct tm));
  if(strptime(argv[1], argv[2], &tm) == NULL) {
    err_exit("Erron on strptime, %s\n", strerror(errno));
  }

  tm.tm_isdst = -1;
  if(argc > 3) {
    printf("%s\n", my_strftime(argv[3], &tm));
  } else {
    printf("%s\n", my_strftime(NULL, &tm));
  }

  exit(EXIT_SUCCESS);
}
