#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int c, prev, state;
    prev = 0;
    state = OUT;
    while ((c = getchar()) != EOF)
    {
        
        if (c == '/' || (c == '*' && prev == '/'))
            state = IN;
        if (c == '\n')
            state = OUT;
        if (c == '/' && prev == '*')
        {
            c = 0;
            state = OUT;
        }

        prev = c;

        if(prev != 0 && state == OUT)
            putchar(prev);

    }

    putchar(c);

    return 0;
}

