
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_LEN 50


int main()
{
    void itoav2(int n, char *s);

    int num = -14543254;
    char res[MAX_LEN];
    printf("Digit: %d\n", num);
    itoav2(num, res);
    printf("String: %s\n", res);

    num = INT_MIN;
	printf("Digit: %d\n", num);
    itoav2(num, res);
    printf("String: %s\n", res);

	num = INT_MAX;
	printf("Digit: %d\n", num);
    itoav2(num, res);
    printf("String: %s\n", res);
    
    num = -12345;
	printf("Digit: %d\n", num);
    itoav2(num, res);
    printf("String: %s\n", res);

    return 0;
}

/* itoa: converts number to string */
void itoav2(int n, char *s)
{
    void reverse(char *s);

    int sign = n;
    char *sStart = s; 

    do {
        *s++ = abs(n % 10) + '0';
    } while (n /= 10);

    if (sign < 0)
        *s++ = '-';
        
    *s = '\0';
    reverse(sStart);
}

void reverse(char *s)
{
    int c;
    char *t = s + (strlen(s)-1);

    while (s < t) {
        c = *s, *s = *t, *t = c;
        s++, t--;
    }
}

