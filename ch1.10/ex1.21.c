#include <stdio.h>

int main()
{
    int c;
    int nspace;
    int n;

    nspace = 0;
    n = 4;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            ++nspace;
        else
        {
            if (nspace >= n)
            {
                putchar('\t');
                nspace -= n;
            }

            while (nspace > 0)
            {
                putchar(' ');
                --nspace;
            }

            nspace = 0;
            putchar(c);
        }
    }

    return 0;
}
