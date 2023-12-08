#include <stdio.h>

int lower(int c);

int main(){
    char  character = 'T';
    printf("Original character: %c, converted to lower case: %c\n", character, lower(character));
    return 0;
}

int lower(int c)
{
    if (c>= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    return c;
}
