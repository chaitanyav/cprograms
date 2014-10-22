#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void launch_debuggie() {
  fprintf(stdout, "launching the debuggie\n");
  if(ptrace(PT_TRACE_ME, 0, NULL, NULL)) {
    fprintf(stderr, "Error on ptrace code is %d, reason is %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

void launch_debugger() {

}

int main(int argc, char *argv[]) {
  pid_t child;
  child = fork();
  if(child == 0) {
    printf("Parent pid is:%u Child pid is:%u\n", getppid(), child);
    launch_debuggie();
  } else if(child > 0) {
    printf("Parent pid is:%u Child pid is:%u\n", getppid(), child);
    launch_debugger();
  } else {
    fprintf(stderr, "Error on fork %d, reason %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
