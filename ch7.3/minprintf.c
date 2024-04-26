#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

int main(void)
{
    minprintf("%c\n", 'A');

    minprintf("%d\n", 12345);

    minprintf("%e\n", 123456.789);
    
    minprintf("%g\n", 123.456);

    minprintf("%s\n", "Hello, World!");

    int o = 010;
    minprintf("Octal: %o, decimal: %d\n", o, o);

    int h = 10;
    minprintf("Hex: %x, decimal: %d\n", h, h);

    minprintf("%f\n", 3.14159);

    int x = 123;
    minprintf("%p\n", (void *)&x);

    char *name = "Alice";
    int age = 30;
    double height = 5.8;
    minprintf("Name: %s, Age: %d, Height: %f\n", name, age, height);
    
    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap; /* pointer into unnamed args */
    char *p, *sval;
    char cval;
    int ival;
    double dval;
    void *pval;

    va_start(ap, fmt); /* set ap to 1st arg without name */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'c':
            cval = va_arg(ap, int);
            printf("%c", cval);
            break;
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'e':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'E':
            dval = va_arg(ap, double);
            printf("%E", dval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'g':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case 'G':
            dval = va_arg(ap, double);
            printf("%G", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'o':
            ival = va_arg(ap, int);
            printf("%o", ival);
            break;
        case 'O':
            ival = va_arg(ap, int);
            printf("%O", ival);
            break;
        case 'p': 
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        case 'x':
            ival = va_arg(ap, int);
            printf("%x", ival);
            break;
        case 'X':
            ival = va_arg(ap, int);
            printf("%X", ival);
            break;
        default:
            putchar(*sval);
            break;
        }
    }
    va_end(ap);
}
