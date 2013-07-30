/*
 * Author: NagaChaitanya Vellanki
 *
 * program to demonstrate the effect of O_DSYNC on file write with
 * varying buffer size
 *
 * Use run_stats_file_write_with_buf_sizes_o_dsync.sh to run this program
 * with varying buffer size
 */

#define NUM_BYTES 5000
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void write_data(int buf_size) {
  FILE *file;
  int fd;
  char *buf;
  int i = 0;

  fd = open("bar.txt", O_CREAT | O_WRONLY | O_DSYNC | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);

  if(fd != -1) {
    file = fdopen(fd, "w");

    if(file != NULL) {
      buf = (char *)malloc(sizeof(char) * buf_size);
      if(setvbuf(file, buf, _IOFBF, buf_size) != 0) {
        perror("Error on setvbuf,");
        exit(EXIT_FAILURE);
      }

      for(i = 0; i <= NUM_BYTES; i++) {
        fputc('0', file);
      }

      free(buf);
      fclose(file);
    } else {
      perror("Error on fdopen,");
    }
  } else {
    perror("Error on open,");
    exit(EXIT_FAILURE);
  }

}

int main(int argc, char *argv[]) {
  int buf_size;
  if(argc < 2 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s buf_size\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  buf_size = atoi(argv[1]);
  if(buf_size > 0) {
    write_data(buf_size);
  } else {
    printf("buf_size should be greater than zero\n");
  }

  exit(EXIT_SUCCESS);
}
