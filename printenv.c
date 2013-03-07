/*
 *
 * Author: NagaChaitanya Vellanki
 *
 *
 *  printenv command implementation
 *
 */

#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<getopt.h>

typedef enum {false, true} bool;

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void print_usage(void) {
  fprintf(stdout, "Usage: printenv [OPTION]... [VARIABLE]\n" "Print the values of the specified environment variable(s)\n" "If no VARIABLE is specified, print name and value pairs for them all.\n" "\n" " -0 end each output line with 0 byte rather than newline\n" " -h to display help information and exit\n");
  exit(EXIT_SUCCESS);
}

void print_output(bool newline, const char *str) {
  if(newline) {
    printf("%s\n", str);;
  } else {
    printf("%s", str);
  }
}


int main(int argc, char *argv[], char *envp[]) {
  int option;
  int i;
  bool newline;
  char **ep;
  char *temp;

  newline = true;

  while((option = getopt(argc, argv, "0h")) != -1) {
    switch(option) {
      case '0': newline = false;
                break;
      case 'h': print_usage();
      default: err_exit("Try 'printenv -h' for more information.\n");
    }
  }

  if(optind == argc) {
    for(ep = envp; *ep != NULL; ep++) {
      print_output(newline, *ep);
    }
  } else {
    for(i = optind; i < argc; i++) {
      temp = getenv(argv[i]);
      if(temp != NULL) {
        print_output(newline, temp);
      }
    }
  }

  exit(EXIT_SUCCESS);
}
