#include <stdio.h>

/* echo: output command line args; 1st version */
int main(int argc, char *argv[])
{
    while (--argc > 0)
        //printf("%s%s", *++argv, (argc > 1) ? " " : "");
        printf((argc > 1) ? "%s " : "%s", *++argv);
    printf("\n");
    return 0;
}



