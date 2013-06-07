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
  struct tm *tmp;
  time_t timep;

  char *printable_time = NULL;

  if(gettimeofday(&tv, &tz) == -1) {
    err_exit("Erron on gettimeofday %s\n", strerror(errno));
  }

  printf("Seconds since 00:00:00 1 Jan 1970 UTC: %ld\n", tv.tv_sec);
  printf("Microseconds: %ld\n", tv.tv_usec);

  if(time(&timep) == -1) {
    err_exit("Error on time %s\n", strerror(errno));
  }

  printf("Seconds since 00:00:00 1 Jan 1970 UTC: %ld\n", timep);
  printf("Seconds since 00:00:00 1 Jan 1970 UTC: %ld\n", time(NULL));

  if((printable_time = ctime(&timep)) != NULL) {
  printf("\nPrintable form of time_t: %s", printable_time);
  } else {
    err_exit("Error on ctime %s\n", strerror(errno));
  }

  if((tmp = gmtime(&timep)) != NULL) {
    printf("\nBroken down time by gmtime\n");
    printf("Seconds %d\n", tmp->tm_sec);
    printf("Minutes %d\n", tmp->tm_min);
    printf("Hours %d\n", tmp->tm_hour);
    printf("Day %d\n", tmp->tm_mday);
    printf("Month %d\n", tmp->tm_mon);
    printf("Year %d\n", tmp->tm_year);
    printf("Week Day %d\n", tmp->tm_wday);
    printf("Year Day %d\n", tmp->tm_yday);
    printf("DST flag %d\n", tmp->tm_isdst);

    printf("Printable form of broken down time by gmtime: %s\n", asctime(tmp));
  } else {
    err_exit("Error on gmtime %s\n", strerror(errno));
  }

  if((timep = mktime(tmp)) != -1) {
    printf("mktime on gmtime %ld\n", timep);
  } else {
    err_exit("Erron on mktime %s\n", strerror(errno));
  }

  tmp = NULL;

  if((tmp = localtime(&timep)) != NULL) {
    printf("\nBroken down time by localtime\n");
    printf("Seconds %d\n", tmp->tm_sec);
    printf("Minutes %d\n", tmp->tm_min);
    printf("Hours %d\n", tmp->tm_hour);
    printf("Day %d\n", tmp->tm_mday);
    printf("Month %d\n", tmp->tm_mon);
    printf("Year %d\n", tmp->tm_year);
    printf("Week Day %d\n", tmp->tm_wday);
    printf("Year Day %d\n", tmp->tm_yday);
    printf("DST flag %d\n", tmp->tm_isdst);

    printf("Printable form of broken down time by localtime: %s\n", asctime(tmp));
  } else {
    err_exit("Error on localtime %s\n", strerror(errno));
  }

  if((timep = mktime(tmp)) != -1) {
    printf("mktime on localtime %ld\n", timep);
  } else {
    err_exit("Erron on mktime %s\n", strerror(errno));
  }

  exit(EXIT_SUCCESS);
}
