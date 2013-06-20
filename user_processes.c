/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * List processes of the user specified on the commandline
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
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


int main(int argc, char *argv[]) {
  char *login, filename[64], read_buf[512];
  struct passwd *pwd;
  DIR *dirp;
  struct dirent *direntp;
  int fd, i;
  size_t num_bytes_read;
  uid_t uid;


  if((argc !=2) || strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s login\n", argv[0]);
  }

  login = argv[1];
  if((pwd = getpwnam(login)) != NULL) {
    uid = pwd->pw_uid;
    printf("%d\n", uid);
    dirp = opendir("/proc");

    if(dirp != NULL) {
      while((direntp = readdir(dirp)) != NULL) {

        if(atoi(direntp->d_name) != 0) {

          sprintf(filename, "/proc/%s/status", direntp->d_name);
          fd = open(filename, O_RDONLY);

          if(fd != -1) {
            if((num_bytes_read = read(fd, read_buf, 512)) != 0) {
              if(num_bytes_read != -1) {
                for(i = 0; i < num_bytes_read; i++) {
                  if(read_buf[i] != '\n') {
                    printf("%c", read_buf[i]);
                  } else {
                    printf("\n");
                  }
                }
              }
            } else {
              err_exit("Error on read, %s\n", strerror(errno));
            }
            close(fd);
          }
        }
      }

      closedir(dirp);
    } else {
      err_exit("Error on opendir, %s\n", strerror(errno));
    }
  } else {
    err_exit("Invalid login, %s\n", argv[1]);
  }

  exit(EXIT_SUCCESS);
}
