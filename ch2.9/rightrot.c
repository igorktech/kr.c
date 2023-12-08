#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
    unsigned x = 0b00001010; 
    int n = 3; 

    unsigned result = rightrot(x, n);

    printf("Result: %u\n", result);
    printf("Correct result: %u\n",0b01000000000000000000000000000001);
    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    while (n-- > 0)
		if ((x & 1) == 1) 
			x = (x >> 1) | ~(~0U >> 1);
		else
			x = x >> 1;

	return x;
}
