/*
 * Program to copy between two files
 * usage cp file1 file2
 *
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUF_SISZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  ssize_t numRead;
  char buf[BUF_SIZE];

  if((argc != 3) || (strcmp(argv[1], "--help") == 0)) {
    printf("%s old-file new-file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Open input and output files */
  inputFd = open(argv[1], O_RDONLY);
  if(inputFd == -1) {
    printf("error opening file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open(argv[2], openFlags, filePerms);

  if(outputFd == -1) {
    printf("error opening file %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  while((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
    if(write(outputFd, buf, numRead) != numRead) {
      printf("could not write the whole buffer\n");
      exit(EXIT_FAILURE);
    }
  }

  if(numRead == -1) {
    printf("error while reading\n");
  }

  if(close(inputFd)) {
    printf("could not close input file descriptor\n");
    exit(EXIT_FAILURE);
  }

  if(close(outputFd)) {
    printf("could not close output file descriptor\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
