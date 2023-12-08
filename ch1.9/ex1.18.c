#include <stdio.h>
#define MAXLINE 1000 /* мксимальная длина строки в потоке */

int _getline(char line[], int maxline);

int main()
{
    int len; /* current line length */
    int i; /* maximum line length */
    char line[MAXLINE]; /* current line */
    while ((len = _getline(line, MAXLINE)) > 0){
        for (i = len-1; i >= 0; --i)
            if (line[i] == ' ' || line[i] == '\t')
                line[i] = '\0';
            else if (line[i] == '\n')
                continue;
            else
                break;
        if (line[0] != '\0' && line[0] != '\n')
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
