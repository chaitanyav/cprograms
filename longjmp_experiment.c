/*
 * Author: NagaChaitanya Vellanki
 *
 * This is an experiment to see what happens if longjmp is called after a
 * function has returned
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

void foo() {

  if(!setjmp(env)) {
    printf("after longjmp call\n");
  }

}

int main(int argc, char *argv[]) {
  foo();
  longjmp(env, 1);
  exit(EXIT_SUCCESS);
}
