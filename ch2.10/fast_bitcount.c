#include <stdio.h>

int fast_bitcount(unsigned x);

int main()
{
    int number = 0b01010101;
    printf("number: %d\t number of bits: %d\n", number, fast_bitcount(number));
    
    return 0;
}

/* fast_bitcount: count bits (ones) in х */ 
int fast_bitcount(unsigned x)
{
    int b = 1;

    if (x==0)
        b--;

    while (x &= (x - 1))
            b++; 

    return b;
}
