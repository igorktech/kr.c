#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    char c;
    if (bufp > 0)
        return buf[--bufp];
    else {
        scanf("%c", &c);
        return c;
    }
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
