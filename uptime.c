/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 * uptime command implementation
 */

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void uptime(double *uptime_secs, double *idle_secs) {
  size_t num_bytes_read;
  int fd;
  char read_buf[128];

  fd = open("/proc/uptime", O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);

  if(fd != -1) {
    if((num_bytes_read = read(fd, read_buf, 128)) != -1) {
      if(sscanf(read_buf, "%lf %lf", &(*uptime_secs), &(*idle_secs)) == 2) {
        close(fd);
      } else
      {
        err_exit("Erron on sscanf, %s, line no %d\n", strerror(errno), __LINE__);
      }
    } else {
      err_exit("Erron on read, %s %d\n", strerror(errno), __LINE__);
    }
  } else {
    err_exit("Error on open, %s %d\n", strerror(errno), __LINE__);
  }
}

void loadavg(double *av1, double *av5, double *av15) {
  size_t num_bytes_read;
  int fd;
  char read_buf[128];

  fd = open("/proc/loadavg", O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
  if(fd != -1) {
    if((num_bytes_read = read(fd, read_buf, 128)) != -1) {
      if(sscanf(read_buf, "%lf %lf %lf", &(*av1), &(*av5), &(*av15)) == 3) {
        close(fd);
      } else {
        err_exit("Erron on sscanf, %s %d\n", strerror(errno), __LINE__);
      }
    } else {
      err_exit("Erron on read, %s %d\n", strerror(errno), __LINE__);
    }
  } else {
    err_exit("Error on open, %s %d\n", strerror(errno), __LINE__);
  }
}

int main(int argc, char *argv[]) {
  time_t real_time;
  struct tm *tmp;
  char out_buf[128];
  int pos = 0, updays = 0, uphours = 0, upminutes = 0, num_users = 0;
  double uptime_secs, idle_secs, av1, av5, av15;
  struct utmp * utmpp;

  /* print real time to out_buf */
  time(&real_time);
  tmp = localtime(&real_time);
  pos = sprintf(out_buf, " %02d:%02d:%02d ", tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
  strcat(out_buf, "up ");
  pos += 3;

  /* print uptime, idle time to out_buf */
  uptime(&uptime_secs, &idle_secs);

  updays = (int) uptime_secs / (60 * 60 * 24);
  if(updays) {
    pos += sprintf(out_buf + pos, "%d day%s, ", updays, (updays != 1) ? "s" : "");
  }

  upminutes = (int) uptime_secs / 60;
  uphours = (int) upminutes/ 60;
  uphours = (int) uphours % 24;
  upminutes = upminutes % 60;

  if(uphours) {
    pos += sprintf(out_buf + pos, "%2d:%2d, ", uphours, upminutes);
  } else {
    pos += sprintf(out_buf + pos, "%d min, ", upminutes);
  }

  /* print num_users to out_buf */
  setutent();
  while((utmpp = getutent()) != NULL) {
    if((utmpp->ut_type == USER_PROCESS) && strlen(utmpp->ut_user)) {
      num_users++;
    }
  }
  endutent();

  pos += sprintf(out_buf + pos, "%2d user%s,  ", num_users, (num_users != 1) ? "s" : "");

  /* print load avg to out_buf */
  loadavg(&av1, &av5, &av15);
  sprintf(out_buf + pos, "load average: %0.2f, %0.2f, %0.2f", av1, av5, av15);
  printf("%s\n", out_buf);

  exit(EXIT_SUCCESS);
}
