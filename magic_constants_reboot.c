/*
 * Author: NagaChaitanya Vellanki
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <linux/reboot.h>

int main() {
  printf("MAGIC2 0x%X\n", LINUX_REBOOT_MAGIC2);
  printf("MAGIC2A 0x%X\n", LINUX_REBOOT_MAGIC2A);
  printf("MAGIC2B 0x%X\n", LINUX_REBOOT_MAGIC2B);
  printf("MAGIC2C 0x%X\n", LINUX_REBOOT_MAGIC2C);
  return 0;

}
