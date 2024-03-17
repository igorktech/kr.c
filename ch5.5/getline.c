
#include <stdio.h>

#define MAXLINE 1000

int _getline(char *line, int max);
int strindex(char *source, char *searchfor);

char pattern[] = "ould"; /* search pattern */

int main ()
{
    char line [MAXLINE];
    int found = 0;
    int index = 0;
    while (_getline(line, MAXLINE) > 0)
        if (index = strindex(line, pattern) >= 0) {
            printf("Index: %d, %s", index, line);
            found++;
        }
    return found;
}

/* getline: read line to s, return length */
int _getline(char *s, int lim)
{
    int c;
    char *sStart = s;

    while (--lim > 0 && (c=getchar ()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - sStart;
}

/* strindex: return index of t in s, else -1 */ 
int strindex(char *s, char *t)
{
    int i, j, k;
    char * sCopy, *tCopy;
    while (*s++ != '\0') {
        for (sCopy=s, tCopy = t; *tCopy!='\0' && *sCopy++==*tCopy++;)
            ;
        if (tCopy > t && *tCopy == '\0')
            return i;
    }
    return -1;
}
