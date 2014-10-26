/* Author: NagaChaitanya Vellanki */
/* Program works only on FreeBSD */

/* Compiling the program
 * cc -Wall -Werror -m32 -g -pg -o debugger debugger.c
 */

/* References:
 * 1. http://www.alexonlinux.com/how-debugger-works
 * 2. http://stereopsis.com/FPU.html
 * 3. Free BSD Kernel source code
*/

/* Sample Output
 * ---------------------------------------------------------------------------
 *
        Parent pid is:2416 Child pid is:16355
        launching the debugger
        Pid is 16355
        Parent pid is:16355 Child pid is:0
        launching the debuggie ./loop, pid is 16356
        Printing General Purpose x86 registers of the child process with pid: 16356
        ---------------------------------------------------------------
        trapno: 0xfffff800
        ebp: 0x2804a660
        eip: 0x2804a660
        esp: 0xffffce10
        esi: 0x2066a380
        edi: 0xfffff800
        eax: 0x1b
        ebx: 0x202
        ecx: 0x3b
        edx: 0xffffce10
        cs:  0x33
        ss:  0x3b
        gs: 0x1b
        fs: 0
        ds: 0
        es: 0
        eflags: 0x202
        ---------------------------------------------------------------
        Printing all flags
        ---------------------------------------------------------------
        CF: 0
        RESERVED: 1
        PF: 0
        AF: 0
        ZF: 0
        SF: 0
        TF: 0
        IF: 1
        DF: 0
        OF: 0
        IOPL: 0
        NT: 0
        RF: 0
        VM: 0
        VM: 0
        VIF: 0
        VIP: 0
        ID: 0
        ---------------------------------------------------------------
        ---------------------------------------------------------------
        Printing Debug x86 registers of the child process with pid: 16356
        ---------------------------------------------------------------
        Debug Address 0:0x13
        Debug Address 1:0x3b
        Debug Address 2:0x3b
        Debug Address 3:0
        Reserved: 0
        Reserved: 0
        Debug Status: 0x2
        Debug Control: 0
        ---------------------------------------------------------------

        Floating point unit information
        ---------------------------------------------------------------
        Floating point environment information
        ---------------------------------------------------------------
        ---------------------------------------------------------------
        Printing Floating Point Control Word
        ---------------------------------------------------------------
        IM (invalid operation mask): 1
        DM (denormalized operand mask): 1
        ZM (divide by zero mask): 1
        OM (overflow mask): 1
        UM (underflow mask): 1
        PM (precision inexact mask): 1
        Reserved: 0x1
        PC (precision control): double precision
        RC (rounding control): round to the nearest whole number
        Status word: 0
        Tag word: 0
        Instruction Pointer: 0
        Code segment selector: 0x33
        opcode last executed: 0
        operand offset: 0x3b
        ---------------------------------------------------------------
        Printing the contents of accumalator: 0
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 1
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 2
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 3
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 4
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 5
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 6
        ---------------------------------------------------------------
        ...
        ---------------------------------------------------------------
        Printing the contents of accumalator: 7
        ---------------------------------------------------------------
        ....
        ---------------------------------------------------------------
         Status Word
        ---------------------------------------------------------------
        0
        ---------------------------------------------------------------
         Padding
        ---------------------------------------------------------------
        ....
        Child process was stopped due to signal Trace/BPT trap
*/

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

void print_fpcontrol_word(uint32_t cw) {
  printf("---------------------------------------------------------------\n");
  printf("Printing Floating Point Control Word\n");
  printf("---------------------------------------------------------------\n");
  printf("IM (invalid operation mask): %d\n", (cw & 1) ? 1 : 0);
  printf("DM (denormalized operand mask): %d\n", ((cw >> 1) & 1) ? 1 : 0);
  printf("ZM (divide by zero mask): %d\n", ((cw >> 2) & 1) ? 1 : 0);
  printf("OM (overflow mask): %d\n", ((cw >> 3) & 1) ? 1 : 0);
  printf("UM (underflow mask): %d\n", ((cw >> 4) & 1) ? 1 : 0);
  printf("PM (precision inexact mask): %d\n", ((cw >> 5) & 1) ? 1 : 0);
  printf("Reserved: %#x\n", ((cw >> 6) & 0x3));

  printf("PC (precision control): ");
  switch((cw >> 8) & 0x3) {
    case 0:
      printf("single precision\n");
      break;
    case 1:
      printf("reserved\n");
      break;
    case 2:
      printf("double precision\n");
      break;
    case 3:
      printf("extended precision\n");
      break;
  }

  printf("RC (rounding control): ");
  switch((cw >> 10) & 0x3) {
    case 0:
      printf("round to the nearest whole number\n");
      break;
    case 1:
      printf("round down toward - infinity\n");
      break;
    case 2:
      printf("round up toward + infinity\n");
      break;
    case 3:
      printf("round toward zero (truncate)\n");
      break;
  }
}

void print_fpregisters(struct fpreg fp_reg_info, pid_t child) {
  printf("\nFloating point unit information\n");
  printf("---------------------------------------------------------------\n");
  printf("Floating point environment information\n");
  printf("---------------------------------------------------------------\n");
  print_fpcontrol_word(fp_reg_info.fpr_env[0]);
  printf("Status word: %#x\n", fp_reg_info.fpr_env[1]);
  printf("Tag word: %#x\n", fp_reg_info.fpr_env[2]);
  printf("Instruction Pointer: %#x\n", fp_reg_info.fpr_env[3]);
  printf("Code segment selector: %#x\n", fp_reg_info.fpr_env[4]);
  printf("opcode last executed: %#x\n", fp_reg_info.fpr_env[5]);
  printf("operand offset: %#x\n", fp_reg_info.fpr_env[6]);

  for(int acc = 0; acc < 8; acc++) {
    printf("---------------------------------------------------------------\n");
    printf("Printing the contents of accumalator: %d\n", acc);
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < 10; i++) {
      printf("%#x\n", fp_reg_info.fpr_acc[acc][i]);
    }
  }


  printf("---------------------------------------------------------------\n");
  printf(" Status Word\n");
  printf("---------------------------------------------------------------\n");
  printf("%#x\n", fp_reg_info.fpr_ex_sw);


  printf("---------------------------------------------------------------\n");
  printf(" Padding\n");
  printf("---------------------------------------------------------------\n");
  for(int i = 0; i < 64; i++) {
    printf("%#x\n", fp_reg_info.fpr_pad[i]);
  }
}

void print_eflags(uint32_t eflags) {
    printf("---------------------------------------------------------------\n");
    printf("Printing all flags\n");
    printf("---------------------------------------------------------------\n");
    printf("CF (carry flag): %d\n", (eflags & 1) ? 1 : 0);
    printf("RESERVED: %d\n", ((eflags >> 1) & 1) ? 1 : 0);
    printf("PF (parity flag): %d\n", ((eflags >> 2) & 1) ? 1 : 0);
    printf("AF (auxillary carry flag): %d\n", ((eflags >> 4) & 1) ? 1 : 0);
    printf("ZF (zero flag): %d\n", ((eflags >> 6) & 1) ? 1 : 0);
    printf("SF (sign flag): %d\n", ((eflags >> 7) & 1) ? 1 : 0);
    printf("TF (trap flag): %d\n", ((eflags >> 8) & 1) ? 1 : 0);
    printf("IF (interrupt flag): %d\n", ((eflags >> 9) & 1) ? 1 : 0);
    printf("DF (direction flag): %d\n", ((eflags >> 10) & 1) ? 1 : 0);
    printf("OF (overflow flag): %d\n", ((eflags >> 11) & 1) ? 1 : 0);
    printf("IOPL (i/o privilege level): %#x\n", (eflags >> 12) & 3);
    printf("NT (nested task flag): %d\n", ((eflags >> 14) & 1) ? 1 : 0);
    printf("RF (resume flag): %d\n", ((eflags >> 16) & 1) ? 1 : 0);
    printf("VM (virtual 8086 mode flag): %d\n", ((eflags >> 17) & 1) ? 1 : 0);
    printf("AC (alignment check flag): %d\n", ((eflags >> 18) & 1) ? 1 : 0);
    printf("VIF (virtual interrupt flag): %d\n", ((eflags >> 19) & 1) ? 1 : 0);
    printf("VIP (virtual interrupt pending flag): %d\n", ((eflags >> 20) & 1) ? 1 : 0);
    printf("ID (id flag): %d\n", ((eflags >> 21) & 1) ? 1 : 0);
    printf("---------------------------------------------------------------\n");
}

void print_gpregisters(struct reg reg_info, pid_t child) {
  printf("Printing General Purpose x86 registers of the child process with pid: %u\n", child);
  printf("---------------------------------------------------------------\n");
  printf(
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
      print_eflags(reg_info.r_eflags);
  printf("---------------------------------------------------------------\n");
}

void print_dbgregisters(struct dbreg debug_reg_info, pid_t child) {
  printf("Printing Debug x86 registers of the child process with pid: %u\n", child);
  printf("---------------------------------------------------------------\n");
  for(int i = 0; i < 8; i++) {
    switch(i) {
      case 0:
      case 1:
      case 2:
      case 3:
          printf("Debug Address %d:", i);
          break;
      case 4:
      case 5: printf("Reserved: ");
              break;
      case 6: printf("Debug Status: ");
              break;
      case 7: printf("Debug Control: ");
              break;
    }
    printf("%#x\n", debug_reg_info.dr[i]);
  }

  printf("---------------------------------------------------------------\n");
}

void handle_child_signal(int signal) {
  printf("I am in the %s handler, pid is %u\n", strsignal(signal), getpid());
}

void launch_debuggie(char *name) {
  printf("launching the debuggie %s, pid is %u\n", name, getpid());
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
  printf("launching the debugger\n");
  printf("Pid is %u\n", getpid());
  if(signal(SIGCHLD, handle_child_signal) == SIG_ERR) {
    fprintf(stderr, "Error on signal call\n");
    exit(EXIT_FAILURE);
  }

  do {
    child = wait(&status);

    struct reg reg_info;
    struct dbreg debug_reg_info;
    struct fpreg fp_reg_info;

    ptrace(PT_GETREGS, child, (caddr_t ) &reg_info, 0);
    ptrace(PT_GETREGS, child, (caddr_t ) &debug_reg_info, 0);
    ptrace(PT_GETFPREGS, child, (caddr_t ) &fp_reg_info, 0);
    print_gpregisters(reg_info, child);
    print_dbgregisters(debug_reg_info, child);
    print_fpregisters(fp_reg_info, child);

    if(WIFSTOPPED(status)) {
      printf("Child process was stopped due to signal %s\n", strsignal(WSTOPSIG(status)));
    }
    if(WIFSIGNALED(status)) {
      printf("Child %u received signal %s\n", child, strsignal(WTERMSIG(status)));
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
    printf("Parent pid is:%u Child pid is:%u\n", getppid(), child);
    launch_debuggie(argv[1]);
  } else if(child > 0) {
    printf("Parent pid is:%u Child pid is:%u\n", getppid(), getpid());
    launch_debugger();
  } else {
    fprintf(stderr, "Error on fork %d, reason %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
