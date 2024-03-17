/* inspired by https://clc-wiki.net/wiki */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define MAXLEN 1000
#define MAXWORD 100
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int _getline(char *, int);

int main()
{
    char line[MAXLEN], name[MAXWORD], defn[MAXWORD], *s;
    int i, len;
    while ((len = _getline(line, MAXLEN)) > 0)
    {
        for (int j = 0; j < len; )
            if (*(s = &line[j]) == '#' && strncmp(s, "#define", 7) == 0)
            { 
                for (j += 7; isspace(line[j]) && j < len; j++)
                    ;

                /* get definition name */
                for (i = 0; (isalnum(line[j]) || line[j] == '_') && i < MAXWORD && j < len; )
                    name[i++] = line[j++];
                name[i] = '\0';

                for ( ; isspace(line[j]) && j < len; j++)
                    ;
                /* get value */
                for (i = 0; !isspace(line[j]) && i < MAXWORD && j < len; )
                    defn[i++] = line[j++];
                defn[i] = '\0';

                install(name, defn);
                break;
            }
            else if (isalpha(line[j]) || line[j] == '_') // look for identifier
            {
                for (i = 0; (isalnum(line[j]) || line[j] == '_') && i < MAXWORD && j < len; )
                    name[i++] = line[j++];
                name[i] = '\0';

                struct nlist *result = lookup(name);

                if (result != NULL)
                    printf("%s", result->defn);
                else 
                    printf("%s", name);
            }
            else
                putchar(line[j++]);
    }
    return 0;
}

int _getline(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar ()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}
