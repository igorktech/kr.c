
// main.c

#include <stdio.h>
#include "mystrcpy.h"

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    // Use the mystrcpy function
    mystrcpy(destination, source);

    // Print the result
    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}
