#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main()
{
    char test[] = "Hello, world!";
    printf("Original: %s\n",test);

    reverse(test);

    printf("Reversed: %s\n", test);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}
