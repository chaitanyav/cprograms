/*
 *
 * s<offset>: seek to the byte offset from the start of the file
 * r<length>: read length bytes from file, starting from current location and
 * display in text form
 * R<length>: read length bytes from file, starting from current location and
 * display in hexadecimal form
 * w<string>: write string characters specified in string at current file
 * offset
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[]) {
  size_t len;
  off_t offset;
  int fd, i, j;
  char *buf;
  ssize_t numRead, numWritten;

  if((argc < 3) || (strcmp(argv[1], "--help") == 0)) {
    printf("Usage %s file {r<length>|R<length>|w<string>|<soffset>}...\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  printf("Input file is %s\n", argv[1]);
  fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if(fd == -1) {
    printf("Error opening the file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  for(i = 2; i < argc; i++) {
    switch(argv[i][0]) {
      case 'r':
      case 'R':
        len = strtol(&argv[i][1], NULL, 10);

        buf = malloc(len);
        if(buf == NULL) {
          printf("Memory allocation failed\n");
          exit(EXIT_FAILURE);
        }

        if((numRead = read(fd, buf, len)) == -1) {
          printf("Error reading from file %s\n", argv[1]);
          exit(EXIT_FAILURE);
        }

        if(numRead == 0) {
          printf("End of file %s\n", argv[1]);
        } else {
          for(j = 0; j < numRead; j++) {
            if(argv[i][0] == 'r') {
              printf("%c", isprint((unsigned char) buf[j]) ? buf[j] : '?');
            } else {
              printf("%02x ", buf[j]);
            }
          }
        }

        printf("\n");
        free(buf);
        break;
      case 'w':
         numWritten = write(fd, &argv[i][1], strlen(&argv[i][1]));
         if(numWritten == -1) {
           printf("Cannot write to %s\n", argv[1]);
           exit(EXIT_FAILURE);
         } else {
           if(fdatasync(fd) == -1) {
             printf("sync to file failed\n");
           }
           printf("Write succeeded %s\n", argv[i]);
           printf("Wrote %zd bytes to %s\n", numWritten, argv[1]);
         }
        break;

      case 's':
          offset = strtol(&argv[i][1], NULL, 10);
          printf("offset is %zd\n", offset);
          if(lseek(fd, offset, SEEK_SET) == -1) {
            printf("could not seek\n");
            exit(EXIT_FAILURE);
          }
           printf("Seek succeeded %s\n", argv[i]);
        break;
      default: printf("Arugment must start with rRws: %s \n", argv[i]);
               exit(EXIT_FAILURE);
    }
  }

  if(close(fd) == -1) {
    printf("Cannot close fd\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
