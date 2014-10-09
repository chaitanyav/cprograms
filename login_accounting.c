#include <stdio.h>
#include <utmpx.h>
#include <time.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  struct utmpx *ut;
  setutxent();

  while((ut = getutxent()) != NULL) {
    printf("Type of the record: %-9.9s\n",
        (ut->ut_type == 0) ? "EMPTY" :
        (ut->ut_type == 1) ? "RUN_LVL" :
        (ut->ut_type == 2) ? "BOOT_TIME" :
        (ut->ut_type == 3) ? "NEW_TIME" :
        (ut->ut_type = 4) ? "OLD_TIME" :
        (ut->ut_type == 5) ? "INIT_PROCESS" :
        (ut->ut_type == 6) ? "LOGIN_PROCESS" :
        (ut->ut_type == 7) ? "USER_PROCESS" :
        (ut->ut_type == 8) ? "DEAD_PROCESS" : "???");
    printf("Process id of the login process: %u\n", ut->ut_pid);
    printf("Terminal Device name: %s\n", ut->ut_line);
    printf("Suffix from the terminal name or id from the inittab: %s\n", ut->ut_id);
    printf("Username: %s\n", ut->ut_user);
    printf("Hostname for remote login or kernel version for run-level messages: %s\n", ut->ut_host);
    printf("Session id: %u\n", ut->ut_session);
    printf("Time: %s", ctime((time_t *) &(ut->ut_tv.tv_sec)));
    if(ut->ut_addr_v6[1] == 0 && ut->ut_addr_v6[2] == 0 && ut->ut_addr_v6[3] == 0) {
      uint32_t address = ntohl(ut->ut_addr_v6[0]);
      printf("ip address: %d.%d.%d.%d\n", (address >> 24) & 0xFF, (address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF);
    } else {
      printf("ip address: %d.%d.%d.%d\n", ut->ut_addr_v6[0], ut->ut_addr_v6[1], ut->ut_addr_v6[2], ut->ut_addr_v6[3]);
    }
    printf("\n\n");
  }

  endutxent();
  return 0;
}

