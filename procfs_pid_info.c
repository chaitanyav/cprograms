/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 *
 */

#include <errno.h>
#include <fcntl.h>
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

int main(int argc, char *argv[]) {
  pid_t pid;
  int fd, i;
  char buf[64], read_buf[1024];
  size_t num_bytes_read;

  pid = getpid();

  /* printing the environment variables
     affecting the process */
  printf("Environment variables affecting current process(%d)\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "/proc/%d/environ", pid);
  printf("%s\n", buf);

  fd = open(buf,O_RDONLY);

  if(fd == -1) {
    err_exit("Error on open, %s\n", strerror(errno));
  }

  while((num_bytes_read = read(fd, read_buf, 1024)) != 0) {
    if(num_bytes_read != -1) {
    for(i = 0; i < num_bytes_read; i++) {
      if(read_buf[i] != '\0') {
        printf("%c", read_buf[i]);
      } else {
        printf("\n");
      }
    }
    } else {
      err_exit("Error on read, %s\n", strerror(errno));
    }
  }

  close(fd);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) info:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/status", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) current working directory:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/cwd", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) commandline arguments:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/cmdline", pid);
  system(buf);
  printf("\n----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Symlink to process(%d) executable:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/exe", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) memory mappings:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/maps", pid);
  system(buf);
  printf("----------------------------------------------\n");


  memset(buf, 0, 64);
  printf("Process(%d) virtual memory:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/mem", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) mounts:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/mounts", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("symlinks to files opened by Process(%d):\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/fd", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("symlink to root directory of Process(%d):\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/root", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("directories of threads for Process(%d):\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/task", pid);
  system(buf);
  printf("----------------------------------------------\n");

  exit(EXIT_SUCCESS);
}
