/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * print process id, name, parent process id and command
 */

#define _GNU_SOURCE
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <search.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

char *read_from_file(int fd, size_t num_bytes) {
  size_t num_bytes_read;
  char *read_buf;

  if(num_bytes == 0) {
    return NULL;
  } else {
    num_bytes++;
    read_buf = (char *)malloc(sizeof(char) * num_bytes);
    if(read_buf != NULL) {
      if((num_bytes_read = read(fd, read_buf, num_bytes)) != 0) {
        if(num_bytes != -1) {
          close(fd);
          read_buf[num_bytes_read] = '\0';
          return read_buf;
        } else {
          return NULL;
        }
      } else {
        return NULL;
      }
    } else {
      return NULL;
    }
  }
}

void print_process_command_line(int pid) {
  int fd, i;
  char filename[64];
  char read_buf[512];
  size_t num_bytes_read;

  sprintf(filename, "/proc/%d/cmdline", pid);

  fd = open(filename, O_RDONLY);
  if(fd != -1) {
    while(((num_bytes_read = read(fd, read_buf, 512)) != 0) && (num_bytes_read != -1)) {
      for(i = 0; i < num_bytes_read; i++) {
        if(read_buf[i] == 0) {
          printf(" ");
        } else {
          printf("%c", read_buf[i]);
        }
      }
    }
    printf("\n");
  }
}

int max_processes() {
  int fd;
  char filename[64];
  char *read_buf;
  int max_procs = 0;
  sprintf(filename, "/proc/sys/kernel/pid_max");

  fd = open(filename, O_RDONLY);
  if(fd != -1) {
    read_buf = read_from_file(fd, 64);

    if(read_buf != NULL) {
      sscanf(read_buf, "%d", &max_procs);
      free(read_buf);
    }
  }

  return max_procs;
}

int *resize_list(int *list, int *current_size) {
  int *new_list;

  new_list = (int *)realloc(list, (sizeof(int) * (*current_size) * 2));

  if(new_list == NULL) {
    err_exit("Error on realloc: %s, %d", strerror(errno), __LINE__);
  }

  (*current_size) *= 2;

  return new_list;
}

int *active_processes(void) {
  DIR *dirp;
  struct dirent *direntp;
  int *proc_list;
  int num_processes = 0;
  int list_index = 0;
  int list_size = 25;
  int pid;

  dirp = opendir("/proc");

  if(dirp != NULL) {
    proc_list = malloc(sizeof(int) * list_size);

    if(proc_list == NULL) {
      err_exit("Error on malloc: %s, line no %d\n", strerror(errno), __LINE__);
    }

    proc_list[0] = num_processes;
    list_index = 1;
    while((direntp = readdir(dirp)) != NULL) {
      pid = atoi(direntp->d_name);
      if(pid != 0) {
        proc_list[list_index++] = pid;
        num_processes++;

        if(list_index >= list_size) {
          proc_list = resize_list(proc_list, &list_size);
        }
      }
    }

    proc_list[0] = num_processes;
    /* assert(num_processes == (list_index - 1)); */
    closedir(dirp);
  } else {
    err_exit("Error on opendir, %s\n", strerror(errno));
  }

  return proc_list;
}

void print_process_tree(int *proc_list) {
  char filename[64], token1[64], token2[64], proc_name[64], *read_buf;
  int fd, i;
  int num_processes = proc_list[0];
  char *str;
  int ppid;

    printf("PID\t%-20s\tPPID\tCOMMAND\n", "NAME");
    printf("--------------------------------------------------\n");
    for(i = 1; i < num_processes; i++) {
      sprintf(filename, "/proc/%d/status", proc_list[i]);

      fd = open(filename, O_RDONLY);
      if(fd != -1) {

        read_buf = read_from_file(fd, 512);
        if(read_buf != NULL) {

          str = strtok(read_buf, "\n");
          while(str != NULL) {
            sscanf(str, "%s %s", token1, token2);

            if(strcmp(token1, "Name:") == 0) {
              sprintf(proc_name, "%s", token2);
            }

            if(strcmp(token1, "PPid:") == 0) {
              ppid = atoi(token2);
            }

            str = strtok(NULL, "\n");
          }

          free(read_buf);
        }
      }
      printf("%d\t%-20s\t%d\t", proc_list[i], proc_name, ppid);
      print_process_command_line(proc_list[i]);
    }
}

int main(int argc, char *argv[]) {
  int *proc_list;
  proc_list = active_processes();
  print_process_tree(proc_list);

  free(proc_list);
  exit(EXIT_SUCCESS);
}
