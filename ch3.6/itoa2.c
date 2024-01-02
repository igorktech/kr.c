#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_LEN 50
void reverse(char s[]);

void itoa(int n, char s[], int w);

int main()
{
    int num = -14543254;
    char res[MAX_LEN];
    printf("Digit: %d\n", num);
    itoa(num, res, 4);
    printf("String: %s\n", res);

    num = INT_MIN;
	printf("Digit: %d\n", num);
    itoa(num, res, 5);
    printf("String: %s\n", res);

	num = INT_MAX;
	printf("Digit: %d\n", num);
    itoa(num, res, 50);
    printf("String: %s\n", res);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

/* itoa: converts number to string */
void itoa(int n, char s[], int w)
{
    int i, sign;
    
    sign = n;
    i = 0;

    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);


    if (sign < 0)
        s[i++] = '-';
    while ((w - i - 1) > 0) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}
