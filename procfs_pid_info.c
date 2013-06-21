/*
 * Author: NagaChaitanya Vellanki
 *
 * Sample output
    ---------------------------------------------------
     * Environment variables affecting current process(9552)
    ----------------------------------------------
    ADOTDIR=/home/naruto/.antigen
    ANTIGEN_DEFAULT_REPO_URL=https://github.com/robbyrussell/oh-my-zsh.git
    COLORTERM=xfce4-terminal
    DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-TmwJUiYUaq,guid=09c3013641fb851ae4a30c6951c3a559
    DEFAULTS_PATH=/usr/share/gconf/xubuntu.default.path
    DESKTOP_SESSION=xubuntu
    DISPLAY=:0.0
    GDMSESSION=xubuntu
    GIO_LAUNCHED_DESKTOP_FILE=/usr/share/applications/exo-terminal-emulator.desktop
    GIO_LAUNCHED_DESKTOP_FILE_PID=2333
    GLADE_CATALOG_PATH=:/usr/share/glade3/catalogs
    GLADE_MODULE_PATH=:/usr/share/glade3/pixmaps
    GLADE_PIXMAP_PATH=:/usr/lib/glade3/modules
    GNOME_KEYRING_CONTROL=/run/user/naruto/keyring-qDker6
    GNOME_KEYRING_PID=1976
    GPG_AGENT_INFO=/run/user/naruto/keyring-qDker6/gpg:0:1
    GREP_COLOR=1;32
    GREP_OPTIONS=--color=auto
    HISTFILE=/home/naruto/.histfile
    HISTSIZE=10000
    HOME=/home/naruto
    LANG=en_US.UTF-8
    LC_CTYPE=en_US.UTF-8
    LESS=-R
    LOGNAME=naruto
    LSCOLORS=Gxfxcxdxbxegedabagacad
    MANDATORY_PATH=/usr/share/gconf/xubuntu.mandatory.path
    OLDPWD=/home/naruto
    PAGER=less
    PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
    PWD=/home/naruto/cprograms
    SAVEHIST=10000
    SESSION_MANAGER=local/ubuntu:@/tmp/.ICE-unix/2048,unix/ubuntu:/tmp/.ICE-unix/2048
    SHELL=/usr/bin/zsh
    SHLVL=2
    SSH_AGENT_PID=2029
    SSH_AUTH_SOCK=/run/user/naruto/keyring-qDker6/ssh
    TERM=xterm-256color
    TEXTDOMAIN=im-config
    TEXTDOMAINDIR=/usr/share/locale/
    TMUX=/tmp//tmux-1000/default,3233,0
    TMUX_PANE=%3
    UBUNTU_MENUPROXY=
    USER=naruto
    WINDOWID=67108868
    XAUTHORITY=/home/naruto/.Xauthority
    XDG_CONFIG_DIRS=/etc/xdg/xdg-xubuntu:/etc/xdg:/etc/xdg
    XDG_CURRENT_DESKTOP=XFCE
    XDG_DATA_DIRS=/usr/share/xubuntu:/usr/local/share/:/usr/share/:/usr/share
    XDG_MENU_PREFIX=xfce-
    XDG_RUNTIME_DIR=/run/user/naruto
    XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
    XDG_SESSION_COOKIE=ad744711540a7110e93406ab51b4bff5-1371776344.832731-474900517
    XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
    ZSH=/home/naruto/.antigen/repos/https-COLON--SLASH--SLASH-github.com-SLASH-robbyrussell-SLASH-oh-my-zsh.git
    _=/home/naruto/cprograms/./procfs_pid_info
    ----------------------------------------------
    Process(9552) info:
    ----------------------------------------------
    Name:   procfs_pid_info
    State:  S (sleeping)
    Tgid:   9552
    Pid:    9552
    PPid:   6180
    TracerPid:      0
    Uid:    1000    1000    1000    1000
    Gid:    1000    1000    1000    1000
    FDSize: 64
    Groups: 4 24 27 30 46 108 124 1000
    VmPeak:     4272 kB
    VmSize:     4208 kB
    VmLck:         0 kB
    VmPin:         0 kB
    VmHWM:       368 kB
    VmRSS:       368 kB
    VmData:       52 kB
    VmStk:       136 kB
    VmExe:         8 kB
    VmLib:      1924 kB
    VmPTE:        28 kB
    VmSwap:        0 kB
    Threads:        1
    SigQ:   0/7756
    SigPnd: 0000000000000000
    ShdPnd: 0000000000000000
    SigBlk: 0000000000010000
    SigIgn: 0000000000000006
    SigCgt: 0000000000000000
    CapInh: 0000000000000000
    CapPrm: 0000000000000000
    CapEff: 0000000000000000
    CapBnd: 0000001fffffffff
    Seccomp:        0
    Cpus_allowed:   ffffffff,ffffffff
    Cpus_allowed_list:      0-63
    Mems_allowed:   00000000,00000001
    Mems_allowed_list:      0
    voluntary_ctxt_switches:        1
    nonvoluntary_ctxt_switches:     126
    ----------------------------------------------
    Process(9552) current working directory:
    ----------------------------------------------
    lrwxrwxrwx 1 naruto naruto 0 Jun 20 20:24 /proc/9552/cwd -> /home/naruto/cprograms
    ----------------------------------------------
    Process(9552) commandline arguments:
    ----------------------------------------------
    ./procfs_pid_info
    ----------------------------------------------
    Symlink to process(9552) executable:
    ----------------------------------------------
    lrwxrwxrwx 1 naruto naruto 0 Jun 20 20:24 /proc/9552/exe -> /home/naruto/cprograms/procfs_pid_info
    ----------------------------------------------
    Process(9552) memory mappings:
    ----------------------------------------------
    00400000-00402000 r-xp 00000000 08:01 677097                             /home/naruto/cprograms/procfs_pid_info
    00601000-00602000 r--p 00001000 08:01 677097                             /home/naruto/cprograms/procfs_pid_info
    00602000-00603000 rw-p 00002000 08:01 677097                             /home/naruto/cprograms/procfs_pid_info
    7f2dc13c4000-7f2dc1582000 r-xp 00000000 08:01 921709                     /lib/x86_64-linux-gnu/libc-2.17.so
    7f2dc1582000-7f2dc1781000 ---p 001be000 08:01 921709                     /lib/x86_64-linux-gnu/libc-2.17.so
    7f2dc1781000-7f2dc1785000 r--p 001bd000 08:01 921709                     /lib/x86_64-linux-gnu/libc-2.17.so
    7f2dc1785000-7f2dc1787000 rw-p 001c1000 08:01 921709                     /lib/x86_64-linux-gnu/libc-2.17.so
    7f2dc1787000-7f2dc178c000 rw-p 00000000 00:00 0
    7f2dc178c000-7f2dc17af000 r-xp 00000000 08:01 921685                     /lib/x86_64-linux-gnu/ld-2.17.so
    7f2dc1998000-7f2dc199b000 rw-p 00000000 00:00 0
    7f2dc19ab000-7f2dc19ae000 rw-p 00000000 00:00 0
    7f2dc19ae000-7f2dc19af000 r--p 00022000 08:01 921685                     /lib/x86_64-linux-gnu/ld-2.17.so
    7f2dc19af000-7f2dc19b1000 rw-p 00023000 08:01 921685                     /lib/x86_64-linux-gnu/ld-2.17.so
    7fff734a0000-7fff734c1000 rw-p 00000000 00:00 0                          [stack]
    7fff735fe000-7fff73600000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    ----------------------------------------------
    Process(9552) virtual memory:
    ----------------------------------------------
    cat: /proc/9552/mem: Permission denied
    ----------------------------------------------
    Process(9552) mounts:
    ----------------------------------------------
    rootfs / rootfs rw 0 0
    sysfs /sys sysfs rw,nosuid,nodev,noexec,relatime 0 0
    proc /proc proc rw,nosuid,nodev,noexec,relatime 0 0
    udev /dev devtmpfs rw,relatime,size=496420k,nr_inodes=124105,mode=755 0 0
    devpts /dev/pts devpts rw,nosuid,noexec,relatime,gid=5,mode=620,ptmxmode=000 0 0
    tmpfs /run tmpfs rw,nosuid,noexec,relatime,size=101188k,mode=755 0 0
    /dev/disk/by-uuid/3d9e6144-3625-45ec-adad-bcfd6a833c46 / ext4 rw,relatime,errors=remount-ro,data=ordered 0 0
    none /sys/fs/cgroup tmpfs rw,relatime,size=4k,mode=755 0 0
    none /sys/fs/fuse/connections fusectl rw,relatime 0 0
    none /sys/kernel/debug debugfs rw,relatime 0 0
    none /sys/kernel/security securityfs rw,relatime 0 0
    none /run/lock tmpfs rw,nosuid,nodev,noexec,relatime,size=5120k 0 0
    none /run/shm tmpfs rw,nosuid,nodev,relatime 0 0
    none /run/user tmpfs rw,nosuid,nodev,noexec,relatime,size=102400k,mode=755 0 0
    vmware-vmblock /run/vmblock-fuse fuse.vmware-vmblock rw,nosuid,nodev,relatime,user_id=0,group_id=0,default_permissions,allow_other 0 0
    gvfsd-fuse /run/user/naruto/gvfs fuse.gvfsd-fuse rw,nosuid,nodev,relatime,user_id=1000,group_id=1000 0 0
    ----------------------------------------------
    symlinks to files opened by Process(9552):
    ----------------------------------------------
    total 0
    lrwx------ 1 naruto naruto 64 Jun 20 20:24 0 -> /dev/pts/7
    lrwx------ 1 naruto naruto 64 Jun 20 20:24 1 -> /dev/pts/7
    lrwx------ 1 naruto naruto 64 Jun 20 20:24 2 -> /dev/pts/7
    ----------------------------------------------
    symlink to root directory of Process(9552):
    ----------------------------------------------
    lrwxrwxrwx 1 naruto naruto 0 Jun 20 20:24 /proc/9552/root -> /
    ----------------------------------------------
    directories of threads for Process(9552):
    ----------------------------------------------
    total 0
    dr-xr-xr-x 6 naruto naruto 0 Jun 20 20:24 9552
    ----------------------------------------------
    ------------------------------------------------------------
 *
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

void err_exit(const char *format, ...) {
  va_list args;

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  pid_t pid;
  int fd, i;
  char buf[64], read_buf[1024];
  size_t num_bytes_read;

  pid = getpid();

  /* printing the environment variables
     affecting the process */
  printf("Environment variables affecting current process(%d)\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "/proc/%d/environ", pid);

  fd = open(buf,O_RDONLY);

  if(fd == -1) {
    err_exit("Error on open, %s\n", strerror(errno));
  }

  while((num_bytes_read = read(fd, read_buf, 1024)) != 0) {
    if(num_bytes_read != -1) {
    for(i = 0; i < num_bytes_read; i++) {
      if(read_buf[i] != '\0') {
        printf("%c", read_buf[i]);
      } else {
        printf("\n");
      }
    }
    } else {
      err_exit("Error on read, %s\n", strerror(errno));
    }
  }

  close(fd);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) info:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/status", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) current working directory:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/cwd", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) commandline arguments:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/cmdline", pid);
  system(buf);
  printf("\n----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Symlink to process(%d) executable:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/exe", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) memory mappings:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/maps", pid);
  system(buf);
  printf("----------------------------------------------\n");


  memset(buf, 0, 64);
  printf("Process(%d) virtual memory:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/mem", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("Process(%d) mounts:\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "cat /proc/%d/mounts", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("symlinks to files opened by Process(%d):\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/fd", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("symlink to root directory of Process(%d):\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/root", pid);
  system(buf);
  printf("----------------------------------------------\n");

  memset(buf, 0, 64);
  printf("directories of threads for Process(%d):\n", pid);
  printf("----------------------------------------------\n");
  sprintf(buf, "ls -l /proc/%d/task", pid);
  system(buf);
  printf("----------------------------------------------\n");

  exit(EXIT_SUCCESS);
}
