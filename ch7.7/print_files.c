#include <stdio.h>
#include <stdlib.h>

#define LINEWIDTH 80
#define LINESPERPAGE 10

int main(int argc, char *argv[]) {
    FILE *fp;
    void print_file(FILE *, FILE *);
    char *prog = argv[0];

    if (argc == 1)
        print_file(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                fprintf(stdout, "\n\n\t\t\tFILE: %s", *argv);
                print_file(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

void print_file(FILE *ifp, FILE *ofp) {
    int c;
    int lineno = 0;
    int pageno = 1;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        if (c == '\n') {
            lineno++;
            if (lineno == LINESPERPAGE) {
                fprintf(stdout, "\n\t\t\tPAGE: %d\n\n", pageno);
                pageno++;
                lineno = 0;
            }
        }
    }
    fprintf(stdout, "\n\t\t\tPAGE: %d\n\n", pageno);
}
