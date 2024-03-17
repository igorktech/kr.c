#include <stdio.h>

void _strcat(char *s, char *t);

int main() 
{
    char destination[15] = "Hello, ";
    char *source = "world!";
    _strcat(destination, source);
    printf("Result: %s\n", destination);
    return 0;
}

void _strcat(char *s, char *t)
{
    while(*++s);
    while(*s++ = *t++);
}

