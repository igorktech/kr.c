#include <ctype.h>
#include <stdio.h>
#include "calc.h"

#define BUFSIZE 100

/* getop: get next operator or it sign */
int getop(char s[])
{
    int i, c;

    static int buf[BUFSIZE];
    static int bufp = 0;
    
    while ((s[0] = c = (bufp > 0) ? buf[--bufp] : getchar()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;

    if (c == '+' || c == '-') {
        int op = c;
        c = (bufp > 0) ? buf[--bufp] : getchar();

        buf[bufp++] = c;

        if (!isdigit(c) && c != '.')
                   return op; /* not a number */
    }
    else if (isalpha(c)) {
        while (isalpha(s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar()))
            ;

        buf[bufp++] = c;

        
        s[i] = '\0';
        if (i == 1) {
            s[0] = tolower(s[0]) - 'a';
            /* printf("var %s\n",s); */
            return VAR;
        }
		int index;
        printf("%s", s);
		index = strindex(s, "sin");
		if (index == 0)
			return FUNC;

		index = strindex(s, "exp");
		if (index == 0)
			return FUNC;

		index = strindex(s, "pow");
		if (index == 0)
			return FUNC;

		return -1;
    }
    else if (!isdigit(c) && c != '.')
        return c; /* not a number */

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar()))
            ;
    if (c == '.') /* collect integer part */
        while (isdigit(s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar()))
            ;

    s[i] = '\0';
    if (c != EOF)
        buf[bufp++] = c;
    return NUMBER;
}

/* strindex: return index of t in s, else -1 */ 
int strindex(char s[], char t[])
{
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

