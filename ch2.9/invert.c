#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned int x = 0b001010; 
    int p = 3;
    int n = 3; 

    unsigned int result = invert(x, p, n);

    printf("Result: %u\n", result);
    printf("Correct result: %u\n",0b000100);
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return x ^ (~(~0 << n) << (p+1-n));
}
