#include <stdio.h>

#define swap(t,x,y) {t tmp = x; x = y; y = tmp;}

int main()
{
    char a = 'a', b = 'b';
    int x = 0, y = 1;

    printf("Before: a = %c, b = %c ", a, b); 
    swap(char, a, b);
    printf("After: a = %c, b = %c\n", a, b); 
    printf("Before: x = %d, y = %d ", x, y);
    swap(int, x, y);
    printf("After: x = %d, y = %d\n", x, y); 

    return 0;
}
