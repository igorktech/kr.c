#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#define BUFFERSIZE 10
#define OFFSET 10
void error(char *fmt, ...);

int main(int argc, char *argv[]) {
    int get(int, long pos, char *buf, int n);
    int fd;
    char buf[BUFFERSIZE];
    int n;
    if (argc != 2)
    {
        error("get: usage: get [filename]");
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY, 0)) == -1) {
                error("cat: can't open %s", argv[1]);
                exit(1);
    }
    else
        n = get(fd, OFFSET, buf, BUFFERSIZE);
        if (write(1, buf, n) != n)
            error("cat: stdout write error");
    exit(0);
}

/* get: read n bite from position pos */
int get(int fd, long pos, char *buf, int n)
{
    if (lseek(fd, pos, 0) >= 0) /* walk to pos */
        return read(fd, buf, n);
    else
        return -1;
}
