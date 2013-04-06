/*
 * Author: NagaChaitanya Vellanki
 *
 * hard to understand switch example
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  switch(3) {
    case 0: while(1) {
              case 3:
                printf("in case 3 ");
                break;
            }
  }

  exit(EXIT_SUCCESS);
}
