/*
 * Author: NagaChaitanya Vellanki
 *
 * tee program
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <getopt.h>

#define BUF_SIZE 1024

typedef enum {false, true} bool;

void sigHandler(int sigNum) {
  printf("\nIgnoring interrupt\n");
}

void printUsage() {
  printf("Usage:\n tee [OPTION] \n\n OPTIONS: \n -a To append to the file\n -i ignore interrupt\n -f file \n\n If file is - it is written to stdout\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int fd, option, i;
  bool append, file;
  mode_t filePerms;
  ssize_t numRead, numWritten;
  char buf[BUF_SIZE];

  file = false;
  append = false;

  /* rw-rw-rw */
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  while((option = getopt(argc, argv, "aif:h")) != -1) {
    printf("%c\n", option);
    switch(option) {

      case 'a':
        append = true;
        break;

      case 'i':
        signal(SIGINT, sigHandler);
        break;

      case 'f':
        file = true;
        if(strcmp(optarg, "-") != 0) {
          if(append) {
            fd = open(optarg, O_WRONLY | O_APPEND, filePerms);
          } else {
            fd = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, filePerms);
          }
        } else {
          fd = STDOUT_FILENO;
        }
        break;

      case 'h': printUsage();

      default: printf("Try -h for more information");
               exit(EXIT_FAILURE);
    }
  }

  if(!file) {
    fd = STDOUT_FILENO;
  }

  /* reading stdin and writing to the file, stdout */
  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if(file && ((numWritten = write(fd, buf, numRead)) == -1)) {
      printf("Write failed to %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    if((fd != STDOUT_FILENO) && (fdatasync(fd) == -1)) {
      printf("Sync failed\n");
    }

    buf[numRead] = '\0';
    printf("%s", buf);
  }

  if(numRead == -1) {
    printf("Read failed from stdin\n");
    exit(EXIT_FAILURE);
  }

  if(close(fd) == -1) {
    printf("Close failed on file descriptor\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
