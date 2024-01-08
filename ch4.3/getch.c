#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;
int valBuf = EOF;
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char s[])
{
    int len = strlen(s);

    while(len > 0)
        ungetch(s[--len]);
}

int getch1(void)
{
    if (valBuf != EOF) {
        int tmp = valBuf;
        valBuf = EOF;

        return tmp;
    }
    return getchar();   
}

void ungetch1(int c)
{
    if (valBuf != EOF)
		printf("ungetch: too many characters\n");
    else
        valBuf = c;
}
