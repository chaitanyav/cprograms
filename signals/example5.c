#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void print_signals() {
  int sig = 0;
  for(sig = 1; sig < NSIG; sig++) {
    printf("Signal: %d, Description: %s\n", sig, strsignal(sig));
  }
}

void print_sigset(const char *prefix, const sigset_t *sigset) {
  int sig = 0, cnt = 0;
  for(sig = 1; sig < NSIG; sig++) {
    if(sigismember(sigset, sig)) {
      cnt++;
      printf("%s%d (%s)\n", prefix, sig, strsignal(sig));
    }
  }
  if(cnt == 0) {
    printf("%s<empty signal set>\n", prefix);
  }
}

int print_sigmask(const char *msg) {
  sigset_t curr_mask;
  if(msg != NULL) {
    printf("%s", msg);
  }
  if(sigprocmask(SIG_BLOCK, NULL, &curr_mask) == -1) {
    return -1;
  }
  print_sigset("\t\t", &curr_mask);
  return 0;
}

int print_pending_sigs(const char *msg) {
  sigset_t pending_sigs;
  if(msg != NULL) {
    printf("%s", msg);
  }

  if(sigpending(&pending_sigs) == -1) {
    return -1;
  }

  print_sigset("\t\t", &pending_sigs);
  return 0;
}

int main(int argc, char *argv[]) {
  print_signals();
  print_pending_sigs(NULL);
  print_sigmask(NULL);
  exit(EXIT_SUCCESS);
}
