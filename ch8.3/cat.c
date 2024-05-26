#include <stdio.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

void error(char *, ...);

/* cat: concat files in order, version 1 */
int main(int argc, char *argv[]) {
    char *prog = argv[0]; /* program name for message */
    int fd = 0; /* default stdin descriptor */
    char buf[BUFSIZ];

    void copy_fd_to_stdout(int fd, char *buf);

    if (argc == 1) /* no args; standard stream */
        copy_fd_to_stdout(fd, buf);
    else
        while (--argc > 0)
            if ((fd = open(argv[1], O_RDONLY, 0)) == -1) {
                error("cat: can't open %s", argv[1]);
                exit(1);
            } else
                copy_fd_to_stdout(fd, buf);

    exit(0);
}

void copy_fd_to_stdout(int fd, char *buf) {
    int n;
    while ((n = read(fd, buf, BUFSIZ)) > 0)
        if (write(1, buf, n) != n)
            error("cat: stdout write error");
}
