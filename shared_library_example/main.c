/*
 * Author: NagaChaitanya Vellanki
 *
 * gcc -c -Wall -Werror -fpic hello.c
 * gcc -shared -o libhello.so hello.o
 * gcc -Wall -o main main.c -L. -lhello
 *
 * ldd main
 *    libhello.so (0x00007ffff7dfc000)
 *    libc.so.6 => /lib64/tls/libc.so.6 (0x0000003fa2500000)
 *    /lib64/ld-linux-x86-64.so.2 (0x0000003fa2100000)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "hello.h"

int main(int argc, char *argv[]) {
  hello();
  exit(EXIT_SUCCESS);
}
