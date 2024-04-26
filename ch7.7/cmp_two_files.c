#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    void filecmp(FILE *,FILE *);
    char *prog = argv[0];

    if (argc != 3)
        fprintf(stderr, "Please, provide two files");
    else {
        if ((fp1 = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
            exit(1);
        }
        if ((fp2 = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, argv[2]);
            exit(1);
        }
        filecmp(fp1, fp2);
        fclose(fp1);
        fclose(fp2);
    }
    exit(0);
}

void filecmp(FILE *fp1, FILE *fp2) {
    char line1[MAXLINE], line2[MAXLINE];
    while ((fgets(line1, MAXLINE, fp1) != NULL) &&
            (fgets(line2, MAXLINE, fp2) != NULL))
        if(strcmp(line1, line2) != 0) {
            printf("line 1: %s\nline 2: %s", line1, line2);
            return;
        }
}
