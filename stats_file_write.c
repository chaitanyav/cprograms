/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Use the run_stats_file_write_with_buf_sizes.sh to run with various
 * buffer sizes
 *
 * /run_stats_file_write_with_buf_sizes.sh                                                                                                                     nvellanki@l-desktop-268
 * Buffer Size: 1
 *  Time:
 *
 * real    1m0.333s
 * user    0m7.228s
 * sys     0m44.591s
 *
 * Buffer Size: 2
 * Time:
 *
 * real    0m35.056s
 * user    0m3.772s
 * sys     0m22.589s

 *  Buffer Size: 4
 *  Time:
 *
 * real    0m22.039s
 * user    0m2.432s
 * sys     0m11.177s
 *
 * Buffer Size: 8
 * Time:
 *
 * real    0m16.441s
 * user    0m1.648s
 * sys     0m6.000s
 *
 * Buffer Size: 16
 * Time:
 *
 * real    0m12.866s
 * user    0m1.224s
 * sys     0m3.048s
 *
 * Buffer Size: 32
 * Time:
 *
 * real    0m11.150s
 * user    0m1.052s
 * sys     0m1.548s
 *
 * Buffer Size: 64
 * Time:
 *
 * real    0m10.264s
 * user    0m0.848s
 * sys     0m0.888s
 *
 * Buffer Size: 128
 * Time:
 *
 * real    0m9.971s
 * user    0m0.880s
 * sys     0m0.416s
 *
 * Buffer Size: 256
 * Time:
 *
 * real    0m9.605s
 * user    0m0.820s
 * sys     0m0.240s
 *
 * Buffer Size: 512
 * Time:
 *
 * real    0m9.544s
 * user    0m0.808s
 * sys     0m0.160s
 *
 * Buffer Size: 1024
 * Time:
 *
 * real    0m9.562s
 * user    0m0.780s
 * sys     0m0.120s
 *
 * Buffer Size: 2048
 * Time:
 *
 * real    0m9.402s
 * user    0m0.808s
 * sys     0m0.068s
 *
 * Buffer Size: 4096
 * Time:
 *
 * real    0m9.386s
 * user    0m0.796s
 * sys     0m0.048s
 *
 * Buffer Size: 16384
 * Time:
 *
 * real    0m9.521s
 * user    0m0.796s
 * sys     0m0.048s
 *
 * Buffer Size: 65536
 * Time:
 *
 * real    0m9.379s
 * user    0m0.796s
 * sys     0m0.060s
 *
 */

#define NUM_BYTES 100000000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_data(int buf_size) {
  FILE *file;
  char *buf;
  int i = 0;

  file = fopen("foo.txt", "w+");
  if(file != NULL) {
    buf = (char *)malloc(sizeof(char) * buf_size);

    if(setvbuf(file, buf, _IOFBF, buf_size) != 0) {
      perror("Error on setvbuf,");
      exit(EXIT_FAILURE);
    }

    for(i = 0; i <= 100000000; i++) {
      fputc('0', file);
    }

    free(buf);
    fclose(file);
  } else {
    perror("Error on fopen,");
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
