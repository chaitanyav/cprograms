/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * Get real, effective and saved set ID's
 */

#define _GNU_SOURCE
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  uid_t ruid, euid, suid;
  gid_t rgid, egid, sgid;

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid, %s\n", strerror(errno));
  }

  if(getresgid(&rgid, &egid, &sgid) == -1) {
    err_exit("Error on getresuid, %s\n", strerror(errno));
  }

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid, %s\n", strerror(errno));
  }

  printf("Real User ID: %d\nEffective User ID: %d\nSaved Set User ID: %d\n", ruid, euid, suid);
  printf("\n");
  printf("Real Group ID: %d\nEffective Group ID: %d\nSaved Set Group ID: %d\n", rgid, egid, sgid);
  exit(EXIT_SUCCESS);
}
