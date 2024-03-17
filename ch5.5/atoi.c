
#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);

int main(){
    printf("string: %s, int: %d\n","123", atoi("123"));
    printf("string: %s, int: %d\n","  -12dd3", atoi("  -12dd3"));

    return 0;
}

/* atoi: convert string s to int */
int atoi(char s[])
{
    int i, n, sign;
   
    while (isspace(*s)) /* skip spaces and etc. */
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    
    for (n = 0; isdigit(*s);s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}
