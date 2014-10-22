/* Reference http://www.alexonlinux.com/how-debugger-works */
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <machine/reg.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void handle_child_signal(int signal) {
  fprintf(stdout, "I am in the %s handler, pid is %u\n", strsignal(signal), getpid());
}

void launch_debuggie(char *name) {
  fprintf(stdout, "launching the debuggie %s, pid is %u\n", name, getpid());
  if(ptrace(PT_TRACE_ME, 0, NULL, 0)) {
    fprintf(stderr, "Error on ptrace code is %d, reason is %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    char *argv[] = {NULL};
    char *env[] = {NULL};
    execve(name, argv, env);
  }
}

void launch_debugger() {
  int status;
  pid_t child;
  fprintf(stdout, "launching the debugger\n");
  fprintf(stdout, "Pid is %u\n", getpid());
  if(signal(SIGCHLD, handle_child_signal) == SIG_ERR) {
    fprintf(stderr, "Error on signal call\n");
    exit(EXIT_FAILURE);
  }

  do {
    child = wait(&status);
    struct reg reg_info;
    ptrace(PT_GETREGS, child, (caddr_t ) &reg_info, 0);
    fprintf(stdout, "Printing registers of the child process with pid: %u\n", child);
    fprintf(stdout, "---------------------------------------------------------------\n");
    fprintf(stdout, "ebp: %u\neip: %u\nss:%u\ngs: %u\nfs: %u\nds: %u\nes: %u\n", reg_info.r_ebp, reg_info.r_eip, reg_info.r_ss, reg_info.r_gs, reg_info.r_fs, reg_info.r_ds, reg_info.r_es);
    fprintf(stdout, "---------------------------------------------------------------\n");
    if(WIFSTOPPED(status)) {
      fprintf(stdout, "Child process was stopped due to signal %s\n", strsignal(WSTOPSIG(status)));
    }
    if(WIFSIGNALED(status)) {
      fprintf(stdout, "Child %u received signal %s\n", child, strsignal(WTERMSIG(status)));
    }
  }while(!WIFEXITED(status));
}

int main(int argc, char *argv[]) {
  pid_t child;

  if(argc != 2) {
    fprintf(stderr, "Usage: %s program_name\n", argv[0]);
    exit(EXIT_FAILURE);
  }


  child = fork();
  if(child == 0) {
    fprintf(stdout, "Parent pid is:%u Child pid is:%u\n", getppid(), child);
    launch_debuggie(argv[1]);
  } else if(child > 0) {
    fprintf(stdout, "Parent pid is:%u Child pid is:%u\n", getppid(), getpid());
    launch_debugger();
  } else {
    fprintf(stderr, "Error on fork %d, reason %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
