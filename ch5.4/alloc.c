#include <stdio.h>

#define ALLOCSIZE 10000 /* memory volume */

static char allocbuf[ALLOCSIZE]; /* memory buffer for alloc */
static char *allocp = allocbuf; /* next vacant position */

char *alloc(int n) /* return pointer to n symbols */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* enough memory */
        allocp += n;
        return allocp - n; /* old p */
    } else /* not enough memory in buffer */
        return 0;
}

void afree(char *p) /* free memory by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

