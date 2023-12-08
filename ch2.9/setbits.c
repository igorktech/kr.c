#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
    unsigned int x = 0b001010; 
    int p = 3;
    int n = 2; 
    unsigned int y = 0b000011;

    unsigned int result = setbits(x, p, n, y);

    printf("Result: %u\n", result);
    printf("Correct result: %u\n",0b001110);
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ~(~(~0 << n) << (p+1-n))) | ((y & ~(~0 << n)) << (p+1-n));

}

