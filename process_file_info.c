/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 *(***********in progress **********************)
 * print info about the files open by processes
 */
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    assert(num_processes == (list_index - 1));
    closedir(dirp);
  } else {
    err_exit("Error on opendir, %s\n", strerror(errno));
  }

  return proc_list;
}

int main(int argc, char *argv[]) {

  active_processes();

  exit(EXIT_SUCCESS);
}
