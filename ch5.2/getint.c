#include <stdio.h>
#include <ctype.h>

#define SIZE 50
int getch(void);
void ungetch(int);

int main()
{
    int n, i, array[SIZE], getint(int *);
    
    for(n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    for (i = 0; i < n; i++)
        printf("Digit: %d\n", array[i]);
    return 0;
}
/* getint: read integer from inout stream into pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch())) /* skip spaces */
        ;
    if (!isdigit(c) && c !=EOF && c != '+' && c != '-') {
        ungetch(c); /* not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
			ungetch(sign == 1 ? '+' : '-');
			return 0;
		}
    }
    for(*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

