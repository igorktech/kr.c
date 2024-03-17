#include <stdio.h>

void _strncpy(char *s,char *t, int n);
void _strncat(char *s,char *t, int n);
int _strncmp(const char *s,const char *t, int n);

int main()
{

const char *str1 = "apple";
    const char *str2 = "orange";
    char buffer[10];
    char destination[20] = "Hello, ";
    const char *source = "World!";

    // Test _strncpy
    _strncpy(buffer, str1, 3);
    printf("After _strncpy: %s\n", buffer);

    // Test _strncmp
    int result1 = _strncmp(str1, "appetizer", 3);
    int result2 = _strncmp(str1, "appetizer", 6);

    // Display the results
    printf("\nComparison result (str1 vs 'appetizer' up to 3 characters): %d\n", result1);
    printf("Comparison result (str1 vs 'appetizer' up to 6 characters): %d\n", result2);

    // Test _strncat
    _strncat(destination, source, 3);
    printf("After _strncat: %s\n", destination);

    return 0;
}
void _strncpy(char *s, char *t, int n)
{
    while ((*s++ = *t++) && --n)
       ; 
    *s = '\0';
}
void _strncat(char *s,char *t, int n)
{
    while(*++s);
    while((*s++ = *t++) && --n)
        ;
    *s = '\0';
}
int _strncmp(const char *s,const char *t, int n)
{
    while((*s++ == *t++) && --n)
        if (*s == '\0')
            return 0;
    return *s - *t;
}
