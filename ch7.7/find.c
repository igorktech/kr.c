#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

int _getline(char *line, int max, FILE *fp);
int find(FILE *fp, char *pattern, int except, int number);

int main(int argc, char *argv[]) {
    int c, except = 0, number = 0, found = 0;
    char *prog = argv[0];
    char *pattern = argv[argc-1];
    
    FILE *fp;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    if (argc < 1)
        fprintf(stderr, "Usage: find -x -n [file1] [file2] pattern\n");
    else if (argc == 1) {
        found = find(stdin, pattern, except, number);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            }

            found += find(fp, pattern, except, number);
            fclose(fp);
            argv++;
        }
    }
    return found;
}

int _getline(char *line, int max, FILE *fp) {
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
        return strlen(line);
}

int find(FILE *fp, char *pattern, int except, int number) {
    char line[MAXLINE];
    long lineno = 0;
    int found = 0;
    while (_getline(line, MAXLINE, fp) > 0) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except) {
            if (number)
                fprintf(stdout, "%ld:", lineno);
            fprintf(stdout, "%s", line);
            found++;
        }
    }
    return found;
}
