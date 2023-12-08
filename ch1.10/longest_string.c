#include <stdio.h>
#define MAXLINE 1000 /* мксимальная длина строки в потоке */

int max; /* maximum line length */
char line[MAXLINE]; /* current line */
char longest[MAXLINE]; /* longest line */

int _getline(void);
void copy(void);

int main()
{
    int len; /* current line length */
    extern int max; /* extern allows to access from other files/function */
    extern char longest[];

    max = 0;
    while ((len = _getline()) > 0)
        if (len > max) {
            max = len;
            copy();
        }
    if (max > 0) /* if line was inserted */
        printf("%s", longest);
    return 0;
}

/* getline: read line into s, return length */
int _getline(void)
{
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: copy from into to */
void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
