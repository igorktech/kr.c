#include <stdio.h>
#include <ctype.h>

#define SIZE 50
int getch(void);
void ungetch(int);

int main()
{
    int n, i;
    double array[SIZE], getfloat(double *);
    
    for(n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    for (i = 0; i < n; i++)
        printf("Float number: %e\n", array[i]);
    return 0;
}
/* getint: read integer from inout stream into pn */
double getfloat(double *pn)
{
    int c, sign;
    double power;

    while (isspace(c = getch())) /* skip spaces */
        ;
    if (!isdigit(c) && c !=EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c); /* not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
			ungetch(sign == 1 ? '+' : '-');
			return 0;
		}
    }

    for(*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    if (c == '.')
        c = getch();

    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10;
    }

    int eSign = 1;

    if (c == 'e' || c == 'E') {
		c = getch();
		if (c == '-') {
			eSign = -1;
			c = getch();
		} 
        else if (c == '+')
			c = getch();
	}

    int ePower = 1.0;
    int eVal = 0;
    for (; isdigit(c); c = getch()) 
        eVal = 10.0 * eVal + (c - '0');

    while(eVal--)
        ePower *= 10;

    if (eSign < 0)
        power *=ePower;
    else
        power /= ePower;

    *pn = *pn / power;
    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}
