/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * TODO: tail: read last n lines from file
 *
 */

#define BUF_SIZE 4096
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void print_usage(int status, char *name) {
  printf("Usage: %s [-n num_lines] file\n", name);
  if(status == EXIT_FAILURE) {
    exit(EXIT_FAILURE);
  } else {
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char *argv[]) {

  int fd;
  FILE *file;
  int c;
  int num_lines;
  char buf[BUF_SIZE];

  if(argc < 2 || (strcmp(argv[1], "--help") == 0)) {
    print_usage(EXIT_SUCCESS, argv[0]);
  }

  while((c = getopt(argc, argv, "n:")) != -1) {
    switch(c) {
      case 'n':
        num_lines = atoi(optarg);
        num_lines = (num_lines > 0) ? num_lines : 10;
        break;
      default:
        print_usage(EXIT_FAILURE, argv[0]);
    }
  }

  if(argc == optind) {
    err_exit("missing file name\n");
  } else {
    if(access(argv[optind], F_OK | R_OK) == -1) {
      err_exit("cannot open %s for reading: %s\n", argv[optind],strerror(errno));
    }
  }

  fd = open(argv[optind], O_RDONLY);
  if(fd != -1) {
    file = fdopen(fd, "r");
    setvbuf(file, buf, _IOLBF, BUF_SIZE);

    /*if(lseek(fd, 0, SEEK_END) == -1) {*/
      /*err_exit("Error on lseek: %s\n", strerror(errno));*/
    /*}*/

    while(fgets(buf, BUF_SIZE, file) != NULL) {
      printf("read line\n");
      printf("%s\n", buf);
    }

    fclose(file);

  } else {
    err_exit("Error on open: %s", strerror(errno));
  }

  exit(EXIT_SUCCESS);
}
