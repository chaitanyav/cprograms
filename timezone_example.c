/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * TZ environment variable affects ctime(), mktime(), localtime() and
 * strftime()
 *
 * Sample outputs
 * --------------------------------------------------------------------------
 *
 *  TZ=":Asia/Singapore" ./timezone_example
 *
 *  ctime() is Fri Jun 14 01:17:53 2013
 *
 *  asctime() is Fri Jun 14 01:17:53 2013
 *
 *  strftime() is Friday June 14 01:17:53 AM 2013 SGT
 * ------------------------------------------------------------
 *  TZ=":Asia/Colombo" ./timezone_example
 *
 *  ctime() is Thu Jun 13 22:48:08 2013
 *
 *  asctime() is Thu Jun 13 22:48:08 2013
 *
 *  strftime() is Thursday June 13 10:48:08 PM 2013 IST
 *  ------------------------------------------------------------
 *  TZ=":Europe/Amsterdam" ./timezone_example
 *
 *  ctime() is Thu Jun 13 19:19:29 2013
 *
 *  asctime() is Thu Jun 13 19:19:29 2013
 *
 *  strftime() is Thursday June 13 07:19:29 PM 2013 CEST
 *  ------------------------------------------------------------
 * Also, you can also play with the locale settings by setting
 *  the LANG, LC_* variables. locale -a will list available locales
 *  on the system
 *
 *  LANG=de_DE ./timezone_example
 *  ctime() is Thu Jun 13 11:12:49 2013
 *
 *  asctime() is Thu Jun 13 11:12:49 2013
 *
 *  strftime() is Donnerstag Juni 13 11:12:49  2013 PDT
 *  ------------------------------------------------------------
 *  LANG=de_DE LC_TIME=it_IT ./timezone_example
 *  ctime() is Thu Jun 13 11:13:17 2013
 *
 *  asctime() is Thu Jun 13 11:13:17 2013
 *
 *  strftime() is giovedgiugno 13 11:13:17  2013 PDT
 *  ------------------------------------------------------------
 *  LANG=zu_ZA ./timezone_example
 *  ctime() is Thu Jun 13 11:17:50 2013
 *
 *  asctime() is Thu Jun 13 11:17:50 2013
 *
 *  strftime() is Lwesine Juni 13 11:17:50  2013 PDT
 */

#define BUF_SIZE 1000
#include <errno.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
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
  time_t real_time;
  struct tm *tmp;

  if(setlocale(LC_ALL, "") == NULL) {
    err_exit("Error on setlocale %s\n", strerror(errno));
  }

  real_time = time(NULL);
  if((tmp = localtime(&real_time)) == NULL) {
    err_exit("Error on localtime, %s\n", strerror(errno));
  }

  printf("ctime() is %s\nasctime() is %s\n", ctime(&real_time), asctime(tmp));
  printf("strftime() is %s\n", my_strftime(NULL, tmp));
  exit(EXIT_SUCCESS);
}
