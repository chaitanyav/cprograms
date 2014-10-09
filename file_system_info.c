/*
 * Author: NagaChaitanya Vellanki
 * Program to print the info of the mounted filesystem
 */

#include <stdio.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[]) {

  struct statvfs statvfsbuf;
  if (statvfs("/", &statvfsbuf) != -1) {

    printf("File system block size: %lu bytes\n", statvfsbuf.f_bsize);
    printf("File system fundamental block size: %lu bytes\n", statvfsbuf.f_frsize);
    printf("Total number of blocks in file system: %u\n", (unsigned int) statvfsbuf.f_blocks);
    printf("Total number of available blocks: %u\n", (unsigned int) statvfsbuf.f_bavail);
    printf("Total number of free blocks: %u\n", (unsigned int) statvfsbuf.f_bfree);
    printf("Total number of i-nodes: %u\n", (unsigned int)statvfsbuf.f_files);
    printf("Total number of free i-nodes: %u\n", (unsigned int)statvfsbuf.f_ffree);
    printf("i-nodes available to unprivileged process: %u\n", (unsigned int)statvfsbuf.f_favail);
    printf("File system id: %lu\n", statvfsbuf.f_fsid);
    printf("Mount flags: %lu\n", statvfsbuf.f_flag);
    printf("Maximum length of file names on this file system : %lu\n", statvfsbuf.f_namemax);
  }
  return 0;
}
