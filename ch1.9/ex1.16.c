#include <stdio.h>
#define MAXLINE 1000 /* мксимальная длина строки в потоке */

int _getline(char line[], int maxline);

int main()
{
    int len; /* current line length */
    int max; /* maximum line length */
    char line[MAXLINE]; /* current line */
    max = 0;
    while ((len = _getline(line, MAXLINE)) > 0)
        printf("len: %d, str: %s",len, line);
    return 0;
}

/* getline: read line into s, return length */
int _getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

