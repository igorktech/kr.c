#include <stdlib.h>
#include <string.h>

#include "tnode.h"
/* talloc: create node type tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) /* creates string duplicate s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
