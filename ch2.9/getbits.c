#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main()
{
    unsigned a = getbits(255, 3, 4);
	printf("%d\n", a);

	unsigned b = getbits(3, 1, 2);
	printf("%d\n", b);
    return 0;
}

/* we want bits starting from left p to right */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1- n)) & ~ (~ 0 << n);
}

