/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 *(***********in progress **********************)
 * prints the files open by processes or the process ids if file path is
 * given
 * sample output
 * ---------------------------------------------------------------------------
 * ./process_file_info
 *
 *   PID: 32429 SYMLINK: /proc/32429/fd/3 PATH: socket:[3122823]
 *   PID: 32429 SYMLINK: /proc/32429/fd/4 PATH: socket:[3122830]
 *   PID: 32429 SYMLINK: /proc/32429/fd/5 PATH: pipe:[3122831]
 *   PID: 32429 SYMLINK: /proc/32429/fd/6 PATH: pipe:[3122831]
 *   PID: 32429 SYMLINK: /proc/32429/fd/7 PATH: pipe:[3122832]
 *   PID: 32429 SYMLINK: /proc/32429/fd/8 PATH: pipe:[3122832]
 *   PID: 32429 SYMLINK: /proc/32429/fd/9 PATH: socket:[312283]
 *
 *
 * Use sudo or run as root to avoid getting permission denied
 * ./process_file_info /dev/null
 *
 *   PID: 32429
 *   PID: 32429
 *   PID: 32429
 *   /proc/25610/fd/16 (readlink: Permission denied)
 *   /proc/25610/fd/17 (readlink: Permission denied)
 *   /proc/25610/fd/18 (readlink: Permission denied)
 *   /proc/25610/fd/19 (readlink: Permission denied)
 *   /proc/25610/fd/20 (readlink: Permission denied)
 *   /proc/25610/fd/21 (readlink: Permission denied)
 *   /proc/25610/fd/22 (readlink: Permission denied)
 *
 */

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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

  int *procs_list = NULL;
  int i = 0;
  DIR *dirp;
  char dirname[128];
  char link[128];
  char path[128];
  struct stat buf;
  ssize_t num_bytes_in_buf;
  struct dirent *direntp;

  if(argc == 2 && strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s [file_path]\n", argv[0]);
  }

  procs_list = active_processes();
  for(i = 1; i <= procs_list[0] + 1; i++) {
    sprintf(dirname, "/proc/%d/fd", procs_list[i]);
    dirp = opendir(dirname);

    if(dirp != NULL) {
      while((direntp = readdir(dirp)) != NULL) {
        sprintf(link, "/proc/%d/fd/%s", procs_list[i], direntp->d_name);
        if(lstat(link, &buf) != -1) {
          if(S_ISLNK(buf.st_mode)) {
            if((num_bytes_in_buf = readlink(link, path, 128)) != -1) {
              path[num_bytes_in_buf] = '\0';
              if(argc == 2 && strcmp(argv[1], path) == 0) {
                printf("PID: %d\n", procs_list[i]);
              } else if(argc == 1){
                printf("PID: %d SYMLINK: %s PATH: %s\n", procs_list[i], link, path);
              }
            } else {
              printf("%s (readlink: %s)\n", link, strerror(errno));
            }
          }
        } else {
          err_exit("Error on lstat: %s, linen no: %d\n", strerror(errno), __LINE__);
        }
      }
    }
  }

  exit(EXIT_SUCCESS);
}
