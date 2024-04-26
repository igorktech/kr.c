#include <stdio.h>


int main(void)
{
    int _getline(char *, int);
    int day, month, year;
    char monthname[20];
    char line[1000]; 
    while (_getline(line, sizeof(line)) > 0) {
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
            printf("valid: %s\n", line); /* 25 Dec 1988 */
        else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
            printf("valid: %s\n", line); /* mm/dd/yy */
        else
            printf("invalid: %s\n", line); /* incorrect string */
    }
    return 0;
}

int _getline(char *s, int lim)
{
    int c;
    char *sStart = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;
    *s = '\0';

    return s - sStart;
}
