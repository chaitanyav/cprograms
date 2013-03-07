/*
 * Author: NagaChaitanya Vellanki
 *
 * tee - read from standard input and write to standard output and files
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <getopt.h>
#include<string.h>

#define BUF_SIZE 1024

typedef enum {false, true} bool;

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void sigHandler(int sigNum) {
  fprintf(stdout, "\nIgnoring interrupt\n");
}

void printUsage() {
  fprintf(stdout, "Usage: tee [OPTION]... [FILE]... \n\
      Copy standard input to each FILE, and also to standard output.\n\
      \n\
      OPTIONS: \n\
      -a To append to the file\n\
      -i ignore interrupt\n\
      -h help\n\n\
      If file is - it is written to stdout\n");
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  int32_t option, i, j, numFiles;
  bool append;
  mode_t filePerms;
  ssize_t numRead, numWritten;
  char buf[BUF_SIZE];
  int32_t *fileDescriptors, *isFile;

  append = false;

  /* rw-rw-rw */
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  while((option = getopt(argc, argv, "aih")) != -1) {
    switch(option) {

      case 'a':
        append = true;
        break;

      case 'i':
        signal(SIGINT, sigHandler);
        break;

      case 'h': printUsage();

      default: err_exit("Try -h for more information\n");
    }
  }

  numFiles = argc - optind;

  if(numFiles) {
    fileDescriptors = malloc(sizeof(int32_t) * numFiles);
    if(fileDescriptors == NULL) {
      err_exit("Memory allocation failed for file descriptors\n");
    }

    isFile = malloc(sizeof(int32_t)* numFiles);
    if(isFile == NULL) {
      err_exit("Memory allocation failed for isFile\n");
    }

    for(i = optind; i < argc ; i++) {
      j = i - optind;
      if(strcmp(argv[i], "-") != 0) {
        isFile[j] = true;

        if(append) {
          fileDescriptors[j] = open(argv[i], O_WRONLY | O_CREAT | O_APPEND, filePerms);
        } else {
          fileDescriptors[j] = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC, filePerms);
        }
      } else {
        isFile[j] = false;
        fileDescriptors[j] = STDOUT_FILENO;
      }
    }
  }

  /* reading stdin and writing to the file, stdout */
  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    for(i = 0; i < numFiles; i++) {
      if((numWritten = write(fileDescriptors[i], buf, numRead)) == -1) {
        err_exit("Write failed to %s\n", argv[i + optind]);
      }

      if(isFile[i] && (fdatasync(fileDescriptors[i]) == -1)) {
        fprintf(stderr, "Sync failed\n");
      }
    }

    buf[numRead] = '\0';
    fprintf(stdout, "%s", buf);
  }

  if(numRead == -1) {
    err_exit("Read failed from stdin\n");
  }

  for(i = 0; i < numFiles; i++) {
    if(close(fileDescriptors[i]) == -1) {
      err_exit("Close failed on file descriptor\n");
    }
  }

  free(fileDescriptors);
  free(isFile);

  exit(EXIT_SUCCESS);
}
