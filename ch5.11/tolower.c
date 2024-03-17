#include <stdio.h>
#include <string.h>

//void _tolower(char *destination, char *source);
//int lower(int c);
//
//int main() {
//    char source[] = "Hello World!";
//    char destination[100]; // Assuming enough space is allocated for the destination
//
//    // Test the tolower function
//    _tolower(destination, source);
//
//    // Print the result
//    printf("Original string: %s\n", source);
//    printf("String in lowercase: %s\n", destination);
//
//    return 0;
//}
void mytolower(char *destination, char *source)
{
    int lower(int c);
    while(*destination++ = lower(*source++))
        ;
}

int lower(int c)
{
   if (c>= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    return c;
}
