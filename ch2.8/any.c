#include <stdio.h>
#include <string.h>
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int any(char s1[], char s2[]);

int main()
{
    printf("idx: %d", any("Hello", "ol"));
}

int any(char s1[], char s2[])
{
    int i, j;
        
    for (i = 0; s1[i]; i++)
        for(j = 0; s2[j]; j++)
            if(s1[i] == s2[j])
                return i;            

    return -1;
}
