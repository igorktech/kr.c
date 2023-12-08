#include <stdio.h>

int atoi(char s[]);

int main(){
    printf("string: %s, int: %d\n","123", atoi("123"));
    printf("string: %s, int: %d\n","12dd3", atoi("12dd3"));

    return 0;
}

/* atoi: convert string s to int */
int atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
