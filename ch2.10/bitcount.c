#include <stdio.h>

int bitcount(unsigned x);

int main()
{
    int number = 0b01010101;
    printf("number: %d\t number of bits: %d\n", number, bitcount(number));
    
    return 0;
}
/* bitcount: count bits (ones) in х */ 
int bitcount (unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1) 
        if (x & 01)
            b++; 

    return b;
}
