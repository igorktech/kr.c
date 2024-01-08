#include <stdio.h>
#include "calc.h"

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
double pop(void)
{
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double top(void)
{
    if (sp > 0)
        return stack[sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void duplicate(void)
{
    if (sp < MAXVAL)
        push(top());
    else
        printf("error: stack full, can't dublicate top\n");
}

void swap(void)
{
    double a, b;
    if (sp >= 2){
        a = pop();
        b = pop();
        push(a);
        push(b);
    }
    else
        printf("error: stack size < 2, can't swap top\n");
}

void empty(void)
{
    sp = 0;
}

