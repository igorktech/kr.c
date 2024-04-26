#include <stdarg.h>
#include <stdio.h>

int minscanf(char *fmt, ...);

int main(void)
{
    char c;
    int i;
    float f;
    char s[100];
    int n;

    n = minscanf("%c", &c);
    printf("Num: %d\n", n);
    printf("Character: %c\n", c);

    n = minscanf("%d", &i);
    printf("Num: %d\n", n);
    printf("Integer: %d\n", i);

    n = minscanf("%f", &f);
    printf("Num: %d\n", n);
    printf("Float: %f\n", f);

    n = minscanf("%s", s);
    printf("Num: %d\n", n);
    printf("String: %s\n", s);

    return 0;
}

int minscanf(char *fmt, ...)
{
    va_list ap; /* ponter into unnamed args */
    char *p, *sval;
    char *cval;
    int *ival;
    float *fval;
    int n;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            continue;
        }
        switch (*++p) {
        case 'c':
            cval = va_arg(ap, char *);
            n = scanf("%c", cval);
            break;
        case 'd':
            ival = va_arg(ap, int *);
            n = scanf("%d", ival);
            break;
        case 'f':
            fval = va_arg(ap, float *);
            n = scanf("%f", fval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            n = scanf("%s", sval);
            break;
        default:
            putchar(*p);
        }
    }
    va_end(ap);
    return n;
}
