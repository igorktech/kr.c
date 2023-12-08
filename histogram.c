#include "stdio.h"

#define SYMBOL_NUM 26 /* lowercase only */
#define DIGIT_NUM 10
int main(void)
{
    int c, i;
    int ndigit[DIGIT_NUM];
    int nsymbol[SYMBOL_NUM];

    for(i = 0; i < DIGIT_NUM; ++i)
        ndigit[i] = 0;

    for(i = 0; i < SYMBOL_NUM; ++i)
        nsymbol[i] = 0;

    while((c = getchar()) != EOF)
    {
        if(c >= 'a' || c <= 'z')
            nsymbol[c-'a'] 
    }
    return 0;
}
