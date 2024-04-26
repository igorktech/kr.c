#include <stdio.h>
#define MAXVAL 100

int sp = 0; /* next stack position */
double stack[MAXVAL]; /* operators stack */

/* push: add element f to stack */
void push(double f)
{
    if (sp < MAXVAL)
        stack[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/*pop: erase element from stack */
double pop()
{
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
