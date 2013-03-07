/*
 * Author: Nagachaitanya Vellanki
 *
 * yes - output a string repeatedly until killed
 */

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

typedef enum {false, true} bool;

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void printUsage() {
  fprintf(stdout, "Usage: yes [STRING]\n   or: yes [OPTION]\nRepeatedly output a line with all specified STRING(s), or `y'.\n");
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  int32_t option, i;

  while((option = getopt(argc, argv, "h")) != -1) {
    switch(option) {
      case 'h': printUsage();
      default: err_exit("Try 'yes -h' for more information.\n", option);
    }
  }

  while(true) {
    if(argc == 1) {
      printf("y\n");
    } else {
      for(i = optind; i < argc; i++) {
        printf("%s", argv[i]);
        if(i == (argc - 1)) {
          printf("\n");
        } else {
          printf(" ");
        }
      }
    }
  }

  exit(EXIT_SUCCESS);
}
