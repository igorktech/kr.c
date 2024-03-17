#include <stdlib.h>
#include <string.h>

char *mystrdup(char *s) /* creates string duplicate s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
