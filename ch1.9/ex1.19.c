#include <stdio.h>
#define MAXLINE 1000 /* мксимальная длина строки в потоке */

int _getline(char line[], int maxline);
void reverse(char line[]);

int main()
{
    int len; /* current line length */
    char line[MAXLINE]; /* current line */
    while ((len = _getline(line, MAXLINE)) > 0){
        reverse(line);
        printf("len: %d, str: %s\n",len, line);

    }

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

void reverse(char s[])
{
    int i, l, r;
    int len;
    int tmp;

    len = 0;
    while(s[len] != '\n')
        ++len;

    l = len-1;
    r = 0;
    while (r < l){
        tmp = s[l];
        s[l] = s[r];
        s[r] = tmp;

        ++r;
        --l;
    }
}

