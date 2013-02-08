/*
 * Author: NagaChaitanya Vellanki
 */

#include <stdio.h>
#include <gnu/libc-version.h>

int main() {

  printf("%s", gnu_get_libc_version());
  return 0;

}
