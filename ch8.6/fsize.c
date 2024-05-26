#define _DARWIN_NO_64_BIT_INODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/dirent.h> // For getdirentries
#include <dirent.h>
#include <time.h>

#define NAME_MAX    255  /* the longest name */
                        /* system dependent */

typedef struct {    /* universal list point */
    long ino;       /* index  number */
    char name[NAME_MAX+1];  /* name + '\0' */
} Dirent;

/* typedef struct {    /1* minimal: no bufffering and etc. *1/ */
/*     int fd;         /1* file descriptor of catalog *1/ */
/*     Dirent d;       /1* list of files *1/ */
/* } MYDIR; */

/* for getdirents to properly read directories */
typedef struct {
    int fd;
    char buf[BUFSIZ];   /* buffer for directory entries */
    int nbytes;         /* number of bytes in buffer */
    char *next;         /* pointer to next directory entry in buffer */
    Dirent d;           /* list of files */
} MYDIR;

MYDIR *myopendir(char *dirname);
Dirent *myreaddir(MYDIR *dfd);
void myclosedir(MYDIR *dfd);

void fsize(char *);
/* <sys/stat.h> */
/* struct stat { */
	/* dev_t           st_dev;         /1* [XSI] ID of device containing file *1/ */
	/* ino_t           st_ino;         /1* [XSI] File serial number *1/ */
	/* mode_t          st_mode;        /1* [XSI] Mode of file (see below) *1/ */
	/* nlink_t         st_nlink;       /1* [XSI] Number of hard links *1/ */
	/* uid_t           st_uid;         /1* [XSI] User ID of the file *1/ */
	/* gid_t           st_gid;         /1* [XSI] Group ID of the file *1/ */
	/* dev_t           st_rdev;        /1* [XSI] Device ID *1/ */
/* #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE) */
	/* struct  timespec st_atimespec;  /1* time of last access *1/ */
	/* struct  timespec st_mtimespec;  /1* time of last data modification *1/ */
	/* struct  timespec st_ctimespec;  /1* time of last status change *1/ */
/* #else */
	/* time_t          st_atime;       /1* [XSI] Time of last access *1/ */
	/* long            st_atimensec;   /1* nsec of last access *1/ */
	/* time_t          st_mtime;       /1* [XSI] Last data modification time *1/ */
	/* long            st_mtimensec;   /1* last data modification nsec *1/ */
	/* time_t          st_ctime;       /1* [XSI] Time of last status change *1/ */
	/* long            st_ctimensec;   /1* nsec of last status change *1/ */
/* #endif */
	/* off_t           st_size;        /1* [XSI] file size, in bytes *1/ */
	/* blkcnt_t        st_blocks;      /1* [XSI] blocks allocated for file *1/ */
	/* blksize_t       st_blksize;     /1* [XSI] optimal blocksize for I/O *1/ */
	/* __uint32_t      st_flags;       /1* user defined flags for file *1/ */
	/* __uint32_t      st_gen;         /1* file generation number *1/ */
	/* __int32_t       st_lspare;      /1* RESERVED: DO NOT USE! *1/ */
	/* __int64_t       st_qspare[2];   /1* RESERVED: DO NOT USE! *1/ */
/* }; */


int main(int argc, char *argv[])
{
    if (argc == 1)     /* defaul current catalog */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

/* int stat(char *, struct stat *); */
void dirwalk(char *, void (*fcn)(char *));
char buff[20];
/* fsize:   output file size */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if (((stbuf.st_mode) & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    strftime(buff, 20, "%b %d %H:%M",localtime (&(stbuf.st_mtime)));
    printf("%8llu %s %s\n", stbuf.st_size, name, buff);
    
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    MYDIR *dfd;

    if ((dfd = myopendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = myreaddir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0
            || strcmp(dp->name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n",
                dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    myclosedir(dfd);
}

#ifndef MYDIRSIZ
#define MYDIRSIZE 255
#endif

struct direct { /* directory entry */
    ino_t d_ino;    /* index number */
    char d_name[MYDIRSIZE];   /* long number doesn't have '\0' */
};

/* int fstat(int fd, struct stat *); */
/*int opendir: open directory for readdir */
MYDIR *myopendir(char  *dirname)
{
    int fd;
    struct stat stbuf;
    MYDIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 ||
        (stbuf.st_mode & S_IFMT) != S_IFDIR ||
        (dp = (MYDIR *) malloc(sizeof(MYDIR))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
}

/* closedir: close catalog opened by opendir */
void myclosedir(MYDIR *dp) {
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

/* #include <sys/dir.h> */
/* #define MYDIRSIZ 255 */

/* /1* readdir: read directory in order *1/ */
/* Dirent *myreaddir(MYDIR *dp) */
/* { */
/*     struct dirent *dirbuf;   /1* local catalog struct *1/ */
/*     static Dirent d; */
/*     static char buf[BUFSIZ]; */ 

/*     int flag = 0; */
/*     while ((flag = read(dp->fd, (char *)&buf, sizeof(buf))) */
/*             == sizeof(buf)) { */
/*         if (dirbuf->d_ino == 0)  /1* cell is free *1/ */
/*             continue; */
/*         dirbuf = (struct dirent *)buf; */
/*         d.ino = dirbuf->d_ino; */
/*         strncpy(d.name, dirbuf->d_name, NAME_MAX); */
/*         d.name[NAME_MAX] = '\0';  /1* ensure ending *1/ */
/*         return &d; */
/*     } */
/*     return NULL; */
/* } */

/* myreaddir: read directory in order */
Dirent *myreaddir(MYDIR *dp) {
    long basep = 0;
    struct dirent *dirbuf; /* local directory entry structure */
    static Dirent d;

    if (dp->next == NULL || dp->next >= dp->buf + dp->nbytes) {
        dp->nbytes = getdirentries(dp->fd, dp->buf, /* getdirentries do not store offset */ 
                (unsigned int)sizeof(dp->buf), &basep); /* getdirentries reads as many entries as possible */
        if (dp->nbytes <= 0) {
            return NULL;
        }
        dp->next = dp->buf;
    }
    dirbuf = (struct dirent *)dp->next;
    dp->next += dirbuf->d_reclen;
    d.ino = dirbuf->d_ino;
    strncpy(d.name, dirbuf->d_name, NAME_MAX);
    d.name[NAME_MAX] = '\0';
    return &d;
}
