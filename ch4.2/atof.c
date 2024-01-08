#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 100
/* double atof(char s[]); */

int main(void)
{
    double sum, myatof(char s[]);
    char line[MAXLINE];
    int _getline(char line[], int max);

    sum = 0;
    while (_getline(line, MAXLINE) > 0)
        printf("\t%e\n", sum += myatof(line));
    return 0;
}

int _getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* atof: convert string s to number type double */
double myatof(char s[])
{
    double val, power;
    int i, sign, pow_sign, exponent;

    for(i = 0; isspace(s[i]); i++) /* skip spaces */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for(val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    
    exponent = 0;
    if (s[i] == 'E' || s[i] == 'e'){
        i++;
        pow_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for(; isdigit(s[i]); i++)
            exponent += 10 * exponent + (s[i] - '0');
    }
    
    return sign * val / power * pow(10,pow_sign * exponent);
}
