/* Reference http://www.alexonlinux.com/how-debugger-works */

/* Sample Output:
 * Parent pid is:1668 Child pid is:7144
 * launching the debugger
 * Pid is 7144
 * Parent pid is:7144 Child pid is:0
 * launching the debuggie ./loop, pid is 7147
 * Printing General Purpose x86 registers of the child process with pid: 7147
 * ---------------------------------------------------------------
 *  trapno: 0xfffff800
 *  ebp: 0x603750
 *  eip: 0x603750
 *  esp: 0xffffddc8
 *  esi: 0x32e0000
 *  edi: 0xfffff800
 *  eax: 0x1b
 *  ebx: 0x202
 *  ecx: 0x3b
 *  edx: 0xffffddc8
 *  cs:  0x43
 *  ss:  0x3b
 *  gs: 0x1b
 *  fs: 0
 *  ds: 0
 *  es: 0
 *  eflags: 0x202
 *  ---------------------------------------------------------------
 *  Printing Debug x86 registers of the child process with pid: 7147
 *  ---------------------------------------------------------------
 *  Debug Address 0:0x13
 *  Debug Address 1:0x3b
 *  Debug Address 2:0x3b
 *  Debug Address 3:0xffffddc8
 *  Reserved: 0
 *  Reserved: 0
 *  Debug Status: 0x2
 *  Debug Control: 0
 *  ---------------------------------------------------------------
 *  Child process was stopped due to signal Trace/BPT trap
 * */
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


void print_gpregisters(struct reg reg_info, pid_t child) {
  fprintf(stdout, "Printing General Purpose x86 registers of the child process with pid: %u\n", child);
  fprintf(stdout, "---------------------------------------------------------------\n");
  fprintf(stdout,
      "trapno: %#x\n"
      "ebp: %#x\n"
      "eip: %#x\n"
      "esp: %#x\n"
      "esi: %#x\n"
      "edi: %#x\n"
      "eax: %#x\n"
      "ebx: %#x\n"
      "ecx: %#x\n"
      "edx: %#x\n"
      "cs:  %#x\n"
      "ss:  %#x\n"
      "gs: %#x\n"
      "fs: %#x\n"
      "ds: %#x\n"
      "es: %#x\n"
      "eflags: %#x\n",
      reg_info.r_trapno,
      reg_info.r_ebp,
      reg_info.r_eip,
      reg_info.r_esp,
      reg_info.r_esi,
      reg_info.r_edi,
      reg_info.r_eax,
      reg_info.r_ebx,
      reg_info.r_ecx,
      reg_info.r_edx,
      reg_info.r_cs,
      reg_info.r_ss,
      reg_info.r_gs,
      reg_info.r_fs,
      reg_info.r_ds,
      reg_info.r_es,
      reg_info.r_eflags);
  fprintf(stdout, "---------------------------------------------------------------\n");
}

void print_dbgregisters(struct dbreg debug_reg_info, pid_t child) {
  fprintf(stdout, "Printing Debug x86 registers of the child process with pid: %u\n", child);
  fprintf(stdout, "---------------------------------------------------------------\n");
  for(int i = 0; i < 8; i++) {
    switch(i) {
      case 0:
      case 1:
      case 2:
      case 3:
          fprintf(stdout, "Debug Address %d:", i);
          break;
      case 4:
      case 5: fprintf(stdout, "Reserved: ");
              break;
      case 6: fprintf(stdout, "Debug Status: ");
              break;
      case 7: fprintf(stdout, "Debug Control: ");
              break;
    }
    fprintf(stdout, "%#x\n", debug_reg_info.dr[i]);
  }

  fprintf(stdout, "---------------------------------------------------------------\n");
}

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
    struct dbreg debug_reg_info;
    ptrace(PT_GETREGS, child, (caddr_t ) &reg_info, 0);
    ptrace(PT_GETREGS, child, (caddr_t ) &debug_reg_info, 0);
    print_gpregisters(reg_info, child);
    print_dbgregisters(debug_reg_info, child);
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
