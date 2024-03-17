#include <stdio.h>
size_t _strlen(char *s);

int main()
{
    char *text = "Hello, world!";
    printf("Length: %zu", _strlen(text));
    return 0;
}
size_t _strlen(char *s)
{
    register const char *start = s;
    for (; *++s;);
    return s - start;
}
/* int _strlen(char *s) */
/* { */
/*     int n; */

/*     for (n = 0; *s != '\0'; s++) */
/*         n++; */
/*     return n; */
/* } */
