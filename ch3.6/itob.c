#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_LEN 50
void reverse(char s[]);

void itob(int n, char s[], int b);

int main()
{
    int num = -14543254;
    char res[MAX_LEN];
    printf("Digit: %d\n", num);
    itob(num, res, 10);
    printf("String: %s\n", res);

    num = 256;
	printf("Digit: %d\n", num);
    itob(num, res, 2);
    printf("String: %s\n", res);


	num = 256;
    printf("Digit: %d\n", num);
    itob(num, res, 8);
    printf("String: %s\n", res);

    num = 256;
	printf("Digit: %d\n", num);
    itob(num, res, 16);
    printf("String: %s\n", res);


    num = INT_MIN;
	printf("Digit: %d\n", num);
    itob(num, res, 16);
    printf("String: %s\n", res);

	num = INT_MAX;
	printf("Digit: %d\n", num);
    itob(num, res, 16);
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


/* itob: converts number to string */
void itob(int n, char s[], int b)
{
    int i, sign;

    sign = n; 
    i = 0;

    do {
        int m = abs(n % b);

        s[i++] = (m < 10) ? (m + '0') : (m - 10 + 'a');
    } while (n /= b);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

