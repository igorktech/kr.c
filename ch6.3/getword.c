#include <stdio.h>
#include <ctype.h>
/* getword: read next word or symbol from stream */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;

    if (c == '"') {
        for ( ; --lim > 0; w++)
            if((*w = getch()) == '"') {
                *++w = '\0';
                return c;
            }
    }
    if (c == '#') {
        for ( ; --lim > 0; w++)
            if ((*w = getch()) == '\n') {
                *w = '\0';
                return c;
            }
    } 
    if (c == '/') {
        *w = getch();
	    if (*w == '/') {
			for ( ; --lim > 0; w++) {
				if ((*w = getch()) == '\n') {
					*++w = '\0';
					return c;
				}
			}
		} else if (*w == '*') {
			for ( ; --lim > 0; w++) {
				if ((*w = getch()) == '*') {
					if ((*++w = getch()) == '/') {
						*++w = '\0';
						return c;
					}
				}
			}
		} else
			ungetch(*w);
	} 

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}
