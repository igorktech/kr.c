#include <stdio.h>

int main()
{
    int c;
    int n;
    int i;

    n = 4;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
            for(i = 0; i < n; ++i)
                putchar(' ');
        else
            putchar(c);
    }
}
