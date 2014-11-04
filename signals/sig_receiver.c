#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t got_sigint = 0;
static int sig_cnt[NSIG];

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

static void handler(int sig) {
  if(sig == SIGINT) {
    got_sigint = 1;
  } else {
    sig_cnt[sig]++;
  }
}

int main(int argc, char *argv[]) {
  int n, num_secs;
  sigset_t pending_mask, blocking_mask, empty_mask;

  printf("%s: PID is %ld\n", argv[0], (long)getpid());

  for(n = 1; n < NSIG; n++) {
    (void)signal(n, handler);
  }

  if(argc > 1) {
    num_secs = atoi(argv[1]);
    sigfillset(&blocking_mask);
    if(sigprocmask(SIG_SETMASK, &blocking_mask, NULL) == -1) {
      printf("Error on sigprocmask: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("%s: sleeping for %d seconds\n", argv[0], num_secs);
    sleep(num_secs);

    if(sigpending(&pending_mask) == -1) {
      printf("Error on sigpending: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("%s: pending signals are: \n", argv[0]);
    print_sigset("\t\t", &pending_mask);

    sigemptyset(&empty_mask);

    if(sigprocmask(SIG_SETMASK, &empty_mask, NULL) == -1) {
      printf("Error on sigprocmask: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  while(!got_sigint) {
    continue;
  }

  for(n = 1; n < NSIG; n++) {
    if(sig_cnt[n] != 0) {
      printf("%s: signal %d caught %d time%s\n", argv[0], n, sig_cnt[n], (sig_cnt[n] == 1) ? "" : "s");
      exit(EXIT_SUCCESS);
    }
  }
  exit(EXIT_SUCCESS);
}
