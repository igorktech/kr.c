#include <ctype.h>
#include <stdio.h>
#include "calc.h"

/* getop: get next operator or it sign */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;

    if (c == '+' || c == '-') {
        int op = c;
        c = getch();

        ungetch(c);

        if (!isdigit(c) && c != '.')
                   return op; /* not a number */
    }
    else if (isalpha(c)) {
        while (isalpha(s[++i] = c = getch()))
            ;

        ungetch(c);
        
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
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
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

