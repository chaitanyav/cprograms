/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * pstree implementation
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

typedef struct process_info {
 char *name;
 int *children;
 int num_children;
} process_info;


void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
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


  dirp = opendir("/proc");

  if(dirp != NULL) {
    proc_list = malloc(sizeof(int) * list_size);

    if(proc_list == NULL) {
      err_exit("Error on malloc: %s, line no %d\n", strerror(errno), __LINE__);
    }

    proc_list[0] = num_processes;
    list_index = 1;
    while((direntp = readdir(dirp)) != NULL) {
      if(atoi(direntp->d_name) != 0) {
        proc_list[list_index++] = atoi(direntp->d_name);
        num_processes++;

        if(list_index >= list_size) {
          proc_list = resize_list(proc_list, &list_size);
        }
      }

    }

    proc_list[0] = num_processes;
    assert(num_processes == (list_index - 1));
  } else {
    err_exit("Error on opendir, %s\n", strerror(errno));
  }

  return proc_list;
}

void extract_ppid_and_name(int fd, char *name, int *ppidp) {
  size_t num_bytes_read;
  char read_buf[512];
  if((num_bytes_read = read(fd, read_buf, 512)) != 0) {
    if(num_bytes_read != -1) {

    }
  }
}

void print_process_tree(int *proc_list) {
  char filename[64];
  int fd;
  int num_processes = proc_list[0];
  int i;
  char pid_str[8];
  char proc_name[64];
  ENTRY item;
  ENTRY *found_item;


  if(hcreate(num_processes) == 0) {
    err_exit("Error on hcreate: %s, %d\n", strerror(errno), __LINE__);
  }

  for(i = 1; i < num_processes; i++) {
    sprintf(filename, "/proc/%d/status", proc_list[i]);

    fd = open(filename, O_RDONLY);
    if(fd != -1) {

        memset(pid_str, 0, 8);
        sprintf(pid_str, "%d", proc_list[i]);
        item.key = pid_str;
    }
  }
}

int main(int argc, char *argv[]) {
  int *proc_list;
  int i;

  proc_list = active_processes();
  print_process_tree(proc_list);

  exit(EXIT_SUCCESS);
}
