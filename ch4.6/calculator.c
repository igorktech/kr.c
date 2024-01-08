#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100
#define MAXVAR 26
/* calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int index;

    double varMap[MAXVAR];
    char varState[MAXVAR];

    while ((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case FUNC:
		        index = strindex(s, "sin");
		        if (index == 0)
			        push(sin(pop()));

		        index = strindex(s, "exp");
		        if (index == 0)
			        push(exp(pop()));

		        index = strindex(s, "pow");
		        if (index == 0) {
                op2 = pop();
                    push(pow(pop(), op2));
                }
                break;
            case VAR:
                if (varState[s[0]] == 1)
                    push(varMap[s[0]]);
                else
                    push(atof(s));
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
            case '=':
                op2 = pop();
                int var = pop();
                varMap[var] = op2;
                varState[var] = 1;
                push(op2);
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
