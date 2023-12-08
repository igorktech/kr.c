#include <stdio.h>

void _strcat(char s[], char t[]);

int main()
{
    char a[10]={"abc"}, b[10]={"def"};

    _strcat(a,b);

    printf("%s",a);
}

/* strcat: concatenate 2 strings*/
void _strcat(char s[], char t[])
{
    // magic
    for (; *s; ++s);
    while (*s++ = *t++);
}
