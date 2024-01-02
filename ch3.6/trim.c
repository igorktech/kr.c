#include <stdio.h>
#include <string.h>

int trim(char s[]);

int main(void)
{
    char test[] = "   Hello, world!   \t\n\n";
    trim(test);
    printf("Trimmed string: %sEnd\n",test);
    return 0;
}

/* trim: delete whitespaces at the end of the string */
int trim(char s[])
{
    int n;
    
    for(n = strlen(s)-1; n >= 0; n--)
        if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}
