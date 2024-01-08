#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 50
void reverse(char s[]);

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

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

/* itoa: converts number to string */
/* void itoa(int n, char s[]) */
/* { */
/*     int i, sign; */

/*     if ((sign = n) < 0) /1* write sign *1/ */
/*         n = -n; /1* make number positive *1/ */

/*     i = 0; */
/*     do { */
/*         s[i++] = n % 10 + '0'; */
/*     } while ((n /= 10) > 0); */
/*     if (sign < 0) */
/*         s[i++] = '-'; */
/*     s[i] = '\0'; */
/*     reverse(s); */
/* } */

/* itoa: converts number to string */
void itoa(int n, char s[])
{
    int i, sign, isMin;
    
    isMin = n != 0 && n == -n;
    if ((sign = n) < 0){ /* write sign */
        if (isMin)
            n /= 10;
        n = -n; /* make number positive */
    }

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);

    if (isMin)
        s[strlen(s)-1] += 1;
}
