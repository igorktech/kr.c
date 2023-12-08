
#include <stdio.h>
#define MAXLINE 1000 /* мксимальная длина строки в потоке */

int _getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len; /* current line length */
    int max; /* maximum line length */
    char line[MAXLINE]; /* current line */
    char longest[MAXLINE]; /* longest line */
    max = 0;
    while ((len = _getline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0) /* if line was inserted */
        printf("%s", longest);
    return 0;
}

/* getline: read line into s, return length */
int _getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1; ++i){
        if((c = getchar()) == '\n')
            break;
        if(c == EOF)
            break;
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy from into to */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

