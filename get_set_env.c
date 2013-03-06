/*
 *
 * Author: NagaChaitanya Vellanki
 *
 *
 *  get or set or unset environment variables
 *  clean environment
 */

#define _BSD_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

extern char **environ;

int main(int argc, char *argv[]) {
  char env_name1[] = "SHELL";
  char env_name2[] = "FOO";
  char env_foo[] = "FOO=BAR";
  char **ep;

  fprintf(stdout, "%s=%s\n", env_name1, getenv(env_name1));
  fprintf(stdout, "%s=%s\n", env_name2, getenv(env_name2));

  if(putenv(env_foo)) {
    fprintf(stderr, "Error while setting the env variable FOO, %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%s=%s\n", env_name2, getenv(env_name2));

  if(setenv("FOO", "GOO", 0) == -1) {
    fprintf(stderr, "Error while setting the env variable FOO, %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%s=%s\n", env_name2, getenv(env_name2));

  if(setenv("FOO", "GOO", 1) == -1) {
    fprintf(stderr, "Error while setting the env variable FOO, %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%s=%s\n", env_name2, getenv(env_name2));


  if(unsetenv("FOO") == -1) {
    fprintf(stderr, "Error while unsetting the env variable FOO, %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%s=%s\n", env_name2, getenv(env_name2));

  if(clearenv()) {
    fprintf(stderr, "Error while clearing the environment variables, %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%s=%s\n", env_name1, getenv(env_name1));
  exit(EXIT_SUCCESS);
}
