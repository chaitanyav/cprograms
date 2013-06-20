/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * List processes of the user specified on the commandline
 *
 * Sample output
 * --------------------------------------------------------------------------
 *  » ./user_processes root
 *  Processes run by root
 *
 *  PID COMMAND
 *  1 /sbin/init
 *  325 upstart-udev-bridge--daemon
 *  330 /sbin/udevd--daemon
 *  508 /usr/sbin/bluetoothd
 *  560 /sbin/udevd--daemon
 *  561 /sbin/udevd--daemon
 *  594 /usr/sbin/cupsd-F
 *  773 upstart-socket-bridge--daemon
 *  879
 *  dhclient-1-v-pf/run/dhclient.eth0.pid-lf/var/lib/dhcp/dhclient.eth0.leaseseth0
 *  947 /usr/sbin/modem-manager
 *  964 NetworkManager
 *  978 /usr/lib/policykit-1/polkitd--no-debug
 *  1098 /sbin/getty-838400tty4
 *  1114 /sbin/getty-838400tty5
 *  1133 /sbin/getty-838400tty2
 *  1139 /sbin/getty-838400tty3
 *  1143 /sbin/getty-838400tty6
 *  1160 acpid-c/etc/acpi/events-s/var/run/acpid.socket
 *  1161 cron
 *  1162 atd
 *  1170 lightdm
 *  1259
 *  /usr/bin/X:0-core-auth/var/run/lightdm/root/:0-nolistentcpvt7-novtswitch-backgroundnone
 *  1468 /usr/lib/accountsservice/accounts-daemon
 *  1575 /sbin/getty-838400tty1
 *  1577 /usr/sbin/console-kit-daemon--no-daemon
 *  1788 /usr/lib/upower/upowerd
 *  1860 lightdm--session-child1219
 *  2217 /usr/lib/udisks2/udisksd--no-debug
 *  ------------------------------------------------------------
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void print_procs_by_login(char *login) {
  char filename[64], read_buf[512], *line, token[20], token1[20], cmdline_file[64];
  struct passwd *pwd;
  DIR *dirp;
  struct dirent *direntp;
  int fd, i;
  size_t num_bytes_read;
  uid_t uid;
  char uid_str[] = "Uid:";

  if((pwd = getpwnam(login)) != NULL) {
    printf("Processes run by %s\n", login);
    printf("\nPID COMMAND\n");

    uid = pwd->pw_uid;
    dirp = opendir("/proc");

    if(dirp != NULL) {

      while((direntp = readdir(dirp)) != NULL) {

        if(atoi(direntp->d_name) != 0) {
          sprintf(filename, "/proc/%s/status", direntp->d_name);
          fd = open(filename, O_RDONLY);

          if(fd != -1) {

            if((num_bytes_read = read(fd, read_buf, 512)) != 0) {

              if(num_bytes_read != -1) {
                line = strtok(read_buf, "\n");

                while(line != NULL) {
                  sscanf(line, "%s", token);

                  if(strcmp(token, uid_str) == 0) {
                    sscanf(line, "%s %s", token, token1);

                    if(atoi(token1) == uid) {
                      sprintf(cmdline_file, "/proc/%s/cmdline", direntp->d_name);

                      if((fd = open(cmdline_file, O_RDONLY)) != -1) {
                        memset(read_buf, 0, 512);

                        if((num_bytes_read = read(fd, read_buf, 512)) != 0) {

                          if(num_bytes_read != -1) {
                            printf("%s ", direntp->d_name);

                            for(i = 0; i < num_bytes_read; i++) {

                              if(read_buf[i] == 0) {
                                printf(" ");
                              } else {
                                printf("%c", read_buf[i]);
                              }
                            }
                            printf("\n");
                          }
                        }
                      }
                    }
                  }
                  line = strtok(NULL, "\n");
                }
              }
            } else {
              err_exit("Error on read, %s\n", strerror(errno));
            }
            close(fd);
          }
        }
      }
      closedir(dirp);
    } else {
      err_exit("Error on opendir, %s\n", strerror(errno));
    }
  } else {
    err_exit("Invalid login, %s\n", login);
  }
}

int main(int argc, char *argv[]) {

  if((argc !=2) || strcmp(argv[1], "--help") == 0) {
    err_exit("Usage: %s login\n", argv[0]);
  }

  print_procs_by_login(argv[1]);

  exit(EXIT_SUCCESS);
}
