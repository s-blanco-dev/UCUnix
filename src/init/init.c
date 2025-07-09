#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fail(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void clear_screen() {
  printf("\033[2J\033[H");
  fflush(stdout);
}

int main(void) {
  if (getpid() != 1) {
    fprintf(stderr, "INIT DEBE SER PID 1\n");
    return EXIT_FAILURE;
  }

  system("/bin/net.sh");
  setenv("PATH", "/sbin:/bin:/usr/bin", 1);

  mkdir("/dev", 0755);
  if (mount("devtmpfs", "/dev", "devtmpfs", 0, "") != 0) {
    fail("Error montando devtmpfs");
  }

  mkdir("/proc", 0555);
  if (mount("proc", "/proc", "proc", 0, "") != 0) {
    fail("Error montando /proc");
  }

  mkdir("/sys", 0555);
  if (mount("sysfs", "/sys", "sysfs", 0, "") != 0) {
    fail("Error montando /sys");
  }

  mkdir("/dev/pts", 0755);
  if (mount("devpts", "/dev/pts", "devpts", 0, "") != 0) {
    fail("Error montando devpts");
  }
  clear_screen();

  int fd = open("/logo", O_RDONLY);
  if (fd >= 0) {
    char buf[1024];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0)
      write(STDOUT_FILENO, buf, n);
    close(fd);
  } else {
    printf("\n");
  }

  printf("UCU UNIX Distribution (UCUNIX) v0.2\n\n");

  while (1) {
    pid_t pid = fork();
    if (pid == 0) {
      int tty = open("/dev/tty1", O_RDWR);
      if (tty < 0) {
        fail("No se pudo abrir /dev/tty1");
      }
      dup2(tty, STDIN_FILENO);
      dup2(tty, STDOUT_FILENO);
      dup2(tty, STDERR_FILENO);
      close(tty);

      execl("/bin/usdSh", "usdSh", NULL);
      fail("Error al ejecutar /bin/usdSh");
    } else if (pid > 0) {
      int status;
      waitpid(pid, &status, 0);
      printf("Shell murió...\n");
    } else {
      fail("fork falló");
    }
  }
  return 0;
}
