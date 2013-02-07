/*
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

#define BUF_SIZE 1024

void sigHandler(int sigNum) {
  printf("\nIgnoring interrupt\n");
}


int main(int argc, char *argv[]) {
  int fd;
  mode_t filePerms;
  ssize_t numRead, numWritten;
  char buf[BUF_SIZE];

  if((argc < 2) || (strcmp(argv[1], "--help") == 0) || (argc > 3)) {
    printf("Usage:\n tee file \n tee -a file\n tee -i file");
    exit(EXIT_FAILURE);
  }

  /* rw-rw-rw */
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  /* Case: tee -a file */
  if((argc == 3) && ((strcmp(argv[1], "-a") == 0) || (strcmp(argv[1], "-i") == 0))) {
    fd = open(argv[2], O_WRONLY | O_APPEND , filePerms);

    if(strcmp(argv[1], "-i") == 0) {
      signal(SIGINT, sigHandler);
    }
  }

  /* Case: tee file */
  if((argc == 2)){
    if((strcmp(argv[1], "-a") == 0) || (strcmp(argv[1], "-i") == 0)) {
      fd = STDOUT_FILENO;
    } else {
      fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC , filePerms);
    }
  }

  /* reading stdin and writing to the file, stdout */
  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if((numWritten = write(fd, buf, numRead)) == -1) {
      printf("Write failed to %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    if(fdatasync(fd) == -1) {
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
