#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* maximum number of strings to sort */
#define MAXLINE 1000
#define TAIL_SIZE 8

char *lineptr[MAXLINES]; /* ponters to strings */

int _getline(char *line, int max);
char *alloc(int n);
void afree(char *p);

int main(int argc, char *argv[])
{
    char line[MAXLINE], *ptr;
    int lineno = 0;
    int n, len, tailStart = 0;

    if (argc == 1)
        n = TAIL_SIZE;
    if (argc == 2 && (*++argv)[0] == '-') {
        n = atoi(++*argv);
        if(n < 1)
            n = TAIL_SIZE;
    } else {
        printf("Usage: tail -number\n");
        return 1;
    }


    while ((len = _getline(line, MAXLINE)) > 0 && lineno < MAXLINES) {
        ptr = alloc(len+1);
        strcpy(ptr, line);
        lineptr[lineno++] = ptr;
    }    

    tailStart = lineno-n >= 0 ? lineno-n : 0;
    while (n-- > 0 && tailStart < lineno)
        printf("%s", lineptr[tailStart++]);
    return 0;
}

int _getline(char *line, int max)
{

    int c;
    char *sStart = line;
    while (--max > 0 && (c = getchar()) && c !=EOF && c != '\n')
        *line++ = c;

    if(c == '\n')
        *line++ = '\n';

    *line = '\0';
    return line - sStart;
}
