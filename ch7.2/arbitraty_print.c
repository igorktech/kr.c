#include <stdio.h>
#include <ctype.h>
#define MAXLEN 100
#define HEXLEN 5

int line(int, int);

int main(void)
{
    int c, pos;
    while ((c = getchar()) != EOF)
        if (iscntrl(c) || c == ' ') {
            pos = line(pos, HEXLEN);
            printf("0X%-3X",c);
            if (c == '\n') {
                pos = 0;
                putchar(c);
            }
        }
        else {
            pos = line(pos, 1);
            putchar(c);
        }
    return 0;
}

int line(int pos, int l)
{
    if (pos + l < MAXLEN)
        return pos + l;
    else
        putchar('\n');
    return l;
}
