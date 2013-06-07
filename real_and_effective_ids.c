/*
 * Author: NagaChaitanya Vellanki
 *
 *
 *
 * program to get the real, effective id of the user, group
 * These can also be found in /proc/PID/status file
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
 printf("Real User ID: %d\nEffective User ID: %d\nReal Group ID %d\nEffective Group ID: %d\n", getuid(), geteuid(), getgid(), getegid());
 exit(EXIT_SUCCESS);
}
