/*
 *
 * Author: NagaChaitanya Vellanki
 *
 *
 * display environment variables
 *
 */
#include<stdio.h>
#include<stdlib.h>

extern char **environ;

int main(int argc, char *argv[], char *envp[]) {
  char **ep;

  /* 1st way */
  fprintf(stdout, "******************************************\n\
      Printing environment variables using char **environ\n\
      ******************************************************\n");
  for(ep = environ; *ep != NULL; ep++) {
    fprintf(stdout, "%s\n", *ep);
  }

  fprintf(stdout, "\n\n");

  /* 2nd way */
  fprintf(stdout, "****************************************\n\
      Printing environment variables using char *envp[]\n\
      ************************************************\n");
  for(ep = envp; *ep != NULL; ep++) {
    fprintf(stdout, "%s\n", *ep);
  }

  exit(EXIT_SUCCESS);
}
