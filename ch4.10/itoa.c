#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 50
void itoa(int n, char s[]);

int main()
{
    int num = -14543254;
    char res[MAX_LEN];
    printf("Digit: %d\n", num);
    itoa(num, res);
    printf("String: %s\n", res);

    num = INT_MIN;
	printf("Digit: %d\n", num);
    itoa(num, res);
    printf("String: %s\n", res);

	num = INT_MAX;
	printf("Digit: %d\n", num);
    itoa(num, res);
    printf("String: %s\n", res);

    return 0;
}

/* itoa: converts number to string */
void itoa(int n, char s[])
{
    int pos = 0;
    if (n < 0) {         
        s[0] = '-';
        pos++;
        n = -n; /* make number positive */
    }
    
    if(n == 0)
        return;

    char c = abs(n % 10) + '0';
    itoa(n / 10, s);
    while (n /= 10) pos++;
    
    s[pos++] = c;
    s[pos] = '\0';
}
