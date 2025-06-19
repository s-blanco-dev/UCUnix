#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
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

  mkdir("/proc", 0555);
  mkdir("/sys", 0555);

  if (mount("proc", "/proc", "proc", 0, "") != 0) {
    fail("Error montando /proc");
  }
  //
  // if (mount("sysfs", "/sys", "sysfs", 0, "") != 0) {
  //   fail("Error al montar /sys");
  // }
  //

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
  execl("/bin/usdSh", "usdSh", NULL);
  fail("Error al ejecutar usdSh");
  return 0;
}
