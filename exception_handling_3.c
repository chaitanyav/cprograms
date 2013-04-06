/*
 * Author: NagaChaitanya Vellanki
 *
 * TRY/THROW/CATCH/FINALLY - example
 * Reference: http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


#define FOO_EXCEPTION (1)
#define BAR_EXCEPTION (2)
#define GOO_EXCEPTION (3)

#define TRY do{ jmp_buf env; switch(setjmp(env)) { case 0: while(1) {
#define CATCH(exception) break; case exception:
#define FINALLY break; } default:
#define END_TRY } }while(0)
#define THROW(exception) longjmp(env, exception)

int main(int argc, char *argv[]) {

  TRY {
    printf("In TRY statement\n");
    THROW(GOO_EXCEPTION);
    printf("not reachable\n");
  }
  CATCH(FOO_EXCEPTION) {
    printf("FOO exception caught\n");
  }
  CATCH(BAR_EXCEPTION) {
    printf("BAR exception caught\n");
  }
  CATCH(GOO_EXCEPTION) {
    printf("GOO exception caught\n");
  }
  FINALLY {
    printf("Finally \n");
  }
  END_TRY;

  exit(EXIT_SUCCESS);
}
