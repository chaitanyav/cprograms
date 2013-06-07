/*
 * Author: NagaChaitanya Vellanki
 *
 *
 */

#define _GNU_SOURCE

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fsuid.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

int main(int argc, char *argv[]) {
  uid_t ruid, euid, suid;
  gid_t rgid, egid, sgid;

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid %s\n", strerror(errno));
  }

  printf("Real User ID: %d\nEffective User ID: %d\nSaved Set User ID: %d\n", ruid, euid, suid);

  if(getresgid(&rgid, &egid, &sgid) == -1) {
    err_exit("Error on getresgid %s\n", strerror(errno));
  }

  printf("\nReal Group ID: %d\nEffective Group ID: %d\nSaved Set Group ID: %d\n", rgid, egid, sgid);

  printf("\nFile system User ID: %d\nFile System Group ID: %d\n", setfsuid(-1), setfsgid(-1));

  /* Step 1 */
  printf("\nModifying the Real User ID: 1000, Effective User ID: 0, Saved Set User ID: 0\n");
  if(setresuid(1000, 0, 0) == -1) {
    err_exit("Error on setresuid %s\n", strerror(errno));
  }

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid %s\n", strerror(errno));
  }

  printf("\nAfter modifying:\nReal User ID: %d\nEffective User ID: %d\nSaved Set User ID: %d\nFile System User ID: %d\n", ruid, euid, suid, setfsuid(-1));

  /* Step 2 */
  printf("\nSetting Real User ID to 2000\n");
  if(setuid(2000) == -1) {
    err_exit("Error on setuid %s\n", strerror(errno));
  }

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid %s\n", strerror(errno));
  }

  printf("\nAfter modifying:\nReal User ID: %d\nEffective User ID: %d\nSaved Set User ID: %d\nFile System User ID: %d\n", ruid, euid, suid, setfsuid(-1));

  /* Step 3 */
  printf("\nSetting Effective User ID to 2000\n");
  if(setreuid(-1, 2000) == -1) {
    err_exit("Error on setreuid %s\n", strerror(errno));
  }

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid %s\n", strerror(errno));
  }

  printf("\nAfter modifying:\nReal User ID: %d\nEffective User ID: %d\nSaved Set User ID: %d\nFile System User ID: %d\n", ruid, euid, suid, setfsuid(-1));

  /* Step 4 */
  printf("\nSetting Effective User ID to 2000, Saved Set User ID to 3000, File System User ID to 4000\n");
  if(setresuid(-1, 2000, 3000) == -1) {
    err_exit("Error on setresuid %s\n", strerror(errno));
  }

  if(getresuid(&ruid, &euid, &suid) == -1) {
    err_exit("Error on getresuid %s\n", strerror(errno));
  }

  printf("\nAfter modifying:\nReal User ID: %d\nEffective User ID: %d\nSaved Set User ID: %d\nFile System User ID: %d\n", ruid, euid, suid, setfsuid(4000));
  exit(EXIT_SUCCESS);
}
