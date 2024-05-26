#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>  

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

char buff[20];

int main(int argc, char *argv[])
{
    if (argc == 1)     /* defaul current catalog */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

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

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[__DARWIN_MAXPATHLEN];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0
            || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n",
                dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

