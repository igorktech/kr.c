#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* maximum number of open files */

typedef struct _iobuf {
    int cnt;    /* number of rest symbols */
    char *ptr;  /* next symbol position */
    char *base; /* buffer pointer */
    int flag;   /* file access mode */
    int fd;     /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ = 01,  /* file open for reading */
    _WRITE = 02, /* file open for writing */
    _UNBUF = 04, /* file open without bufering */
    _EOF = 010,  /* EOF reached in file */
    _ERR = 020   /* error */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#define PERMS 0666 /* allowed read and write */
                   /*for owner, group, rest */

/* fopen: open file with FILE pointer returning */
FILE *_fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;             /* find free space for insetion */
    if (fp >= _iob + OPEN_MAX) /* no space for file */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1) /* current name is not available */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

#include <stdlib.h>

/* _fillbuf: create and fill input buffer */
int _fillbuf(FILE *fp) {
    int bufsize;
    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) /* do not have buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* failed to create buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

/* _flushbuf: flush a buffer */
int _flushbuf(int c, FILE *fp) {
    int bufsize;
    unsigned char uc = c;

    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    } else {
        int n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= _ERR;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    *fp->ptr++ = uc;

    return uc;
}

/* fflush: flush the buffer of fp */
int fflush(FILE *fp) {
    if (fp == NULL) { /* flush all output streams */
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
            if ((fp->flag & _WRITE) && fflush(fp) == EOF)
                return EOF;
        }
        return 0;
    }

    if ((fp->flag & _WRITE) == 0)
        return 0;

    _flushbuf(EOF, fp);
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    return (fp->flag & _ERR) ? EOF : 0;
}

/* fclose: close file fp */
int fclose(FILE *fp) {
    if (fp == NULL)
        return EOF;
    if (fflush(fp) == EOF)
        return EOF;
    if (close(fp->fd) == -1)
        return EOF;
    if (fp->base != NULL)
        free(fp->base);

    fp->flag = 0; /* reset flags */
    fp->cnt = 0;
    fp->ptr = NULL;
    fp->base = NULL;
    fp->fd = -1;

    return 0;
}

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* fseek: reposition file pointer */
int fseek(FILE *fp, long offset, int origin) {
    if ((fp->flag & _READ) && fp->base != NULL) {
        if (origin == SEEK_CUR) /* SEEK_CUR */
            offset -= fp->cnt;
        fp->cnt = 0;
        fp->ptr = fp->base;
    } else if ((fp->flag & _WRITE) && fp->base != NULL) {
        fflush(fp);
    }
    return (lseek(fp->fd, offset, origin) == -1) ? -1 : 0;
}
FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr: */
                       {0, (char *)0, (char *)0, _READ, 0},
                       {0, (char *)0, (char *)0, _WRITE, 1},
                       {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if (argc < 2)
        return 1;
    while (--argc > 0) {
        if ((fp = _fopen(*++argv, "r")) == NULL)
            return 1;
        else {
            while ((c = getc(fp)) != EOF)
                putchar(c);
            fclose(fp);
        }
    }

    fflush(stdout);

    return 0;
}
