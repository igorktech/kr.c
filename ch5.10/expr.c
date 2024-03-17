#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXOP 100

int getop(char *, int argc, char **argv);
void push(double);
double pop(void);

int main(int argc, char* argv[])
{
    int type;
    double op2;
    char s[MAXOP];
    
    if (argc == 1) {
        printf("Usage expr: elements\n");
        return 1;
    }

    while ((type = getop(s ,--argc, ++argv)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
                default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    
    printf("\t%.8g\n", pop());

    return 0;
}


int getop(char *s, int argc, char **argv)
{
    int c;
    char *p = *argv;

    if (argc == 0)
        return EOF;

    while ((*s = c = *p++) == ' ' || c == '\t')
        ;
    *++s = '\0';
    
    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    if (isdigit(c)) /* collect integer part */
        while (isdigit(*s++ = c = *p++))
            ;
    if (c == '.') /* collect integer part */
        while (isdigit(*s++ = c = *p++))
            ;

    *s = '\0';
    
    return NUMBER;
}

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
