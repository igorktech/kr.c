#include <stdio.h>
#include <string.h>

void reverse(char s[], int left, int right);

int main()
{
    char test[] = "Hello, world!";
    printf("Original: %s\n",test);

    reverse(test,0, strlen(test)-1);

    printf("Reversed: %s\n", test);

    return 0;
}

void reverse(char s[], int left, int right)
{
    if(left < right){
        int c;
        c = s[right]; /* possible to call swap */
        s[right] = s[left];
        s[left] = c;
        reverse(s, ++left, --right);
    }
}
