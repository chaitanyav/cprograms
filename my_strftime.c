/*
 *  Author: NagaChaitanya Vellanki
 *
 *see listing 10-2 of LPI book
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 1000

char *my_strftime(const char *format) {
  static char buf[BUF_SIZE];
  time_t t;
  size_t s;
  struct tm *tmp;

  t = time(NULL);
  tmp = localtime(&t);
  if(tmp == NULL) {
    return NULL;
  }

  s = strftime(buf, BUF_SIZE, (format != NULL) ? format: "%A %B %d %I:%M:%S %p %Y %Z", tmp);
  return (s == 0) ? NULL : buf;
}

int main(int argc, char *argv[]) {
  printf("strftime examples\n");
  printf("Default: %s\n", my_strftime(NULL));
  printf("Week day: %s\n", my_strftime("%a %A"));
  printf("Month: %s\n", my_strftime("%b %B"));
  printf("Date and Time: %s\n", my_strftime("%c"));
  printf("Day of the month: %s\n", my_strftime("%d %e"));
  printf("American Date: %s\n", my_strftime("%D"));
  printf("ISO Date: %s\n", my_strftime("%F"));
  printf("Hour: %s\n", my_strftime("%H %I"));
  printf("Day of year: %s\n", my_strftime("%j"));
  printf("Decimal month: %s\n", my_strftime("%m"));
  printf("Minute: %s\n", my_strftime("%M"));
  printf("AM/PM: %s\n", my_strftime("%p %P"));
  printf("24 hour time: %s\n", my_strftime("%R"));
  printf("seconds: %s\n", my_strftime("%S"));
  printf("Time: %s\n", my_strftime("%T"));
  printf("Week day number, sunday week number: %s\n", my_strftime("%u %U"));
  printf("Week day number, monday week number: %s\n", my_strftime("%w %W"));
  printf("Date, time: %s\n", my_strftime("%x %X"));
  printf("Timezone: %s\n", my_strftime("%Z"));
  exit(EXIT_SUCCESS);
}
