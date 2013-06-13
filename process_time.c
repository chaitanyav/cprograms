/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  clock_t cpu_time;
  struct tms buf;
  long clock_ticks = 0;
  int i = 0;

  clock_ticks = sysconf(_SC_CLK_TCK);
  printf("CLOCKS_PER_SEC=%ld, sysconf(_SC_CLK_TCK)=%ld\n", CLOCKS_PER_SEC, clock_ticks);

  for(; i < 9000000; i++) {
    getppid();
  }

  if((cpu_time = clock()) == -1) {
    err_exit("Error on clock() %s\n", strerror(errno));
  }

  if(times(&buf) == -1) {
    err_exit("Error on times() %s\n", strerror(errno));
  }

  printf("clock() %ld, cpu time (clocks per sec) %.2f\n", cpu_time, ((float) cpu_time) / (CLOCKS_PER_SEC));
  printf("user cpu time %.2f, system cpu time %.2f\n", ((float) buf.tms_utime) / clock_ticks, ((float) buf.tms_stime) / clock_ticks);
  exit(EXIT_SUCCESS);
}
