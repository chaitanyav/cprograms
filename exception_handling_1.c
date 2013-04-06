/*
 * Author: NagaChaitanya Vellanki
 *
 * TRY/THROW/CATCH example
 * Reference: http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
 * use gcc -E -P exception_handling_1.c to the output of the preprocessor
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


#define TRY do{ jmp_buf env; if(!setjmp(env)) {
#define CATCH } else {
#define END_TRY } }while(0)
#define THROW longjmp(env, 1)

int main(int argc, char *argv[]) {

  TRY {
    printf("In TRY statement\n");
    THROW;
    printf("not reachable\n");
  }
  CATCH {
    printf("exception caught\n");
  }
  END_TRY;

  exit(EXIT_SUCCESS);
}
