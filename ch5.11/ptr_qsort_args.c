#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAXLINES 5000 /* maximum number of strings to sort */

char *lineptr[MAXLINES]; /* ponters to strings */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void _qsort(void *lineptr[], int left, int right,
        int reverse, int foldcase,
        int (*comp)(void *, void *));
int numcmp(char *, char *);
int dircmp(char *, char *);

int main(int argc, char *argv[])
{
    int nlines; /* number of inserted srtings */
  
    int c, numeric = 0, reverse = 0;
    int foldcase = 0, directory = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    while (--argc > 0 && (*++argv)[0] == '-')
            while(c = *++argv[0])
                switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    foldcase = 1;
                    break;
                case 'd':
                    directory = 1;
                    break;
                default:
                    printf("qsort: illegal option %c\n", c);
                    return 1;
                }
    if (argc != 0) {
        printf("Usage: qsort -n -r\n");
        return 1;
    }

    if (numeric && directory) {
        printf("Cannot combine -n and -d\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric)
        _qsort((void **)lineptr, 0, nlines-1, reverse, foldcase,
                (int (*)(void*,void*))(numcmp));
        else if (directory)
        _qsort((void **)lineptr, 0, nlines-1, reverse, foldcase,
                (int (*)(void*,void*))(dircmp));
        else
        _qsort((void **)lineptr, 0, nlines-1, reverse, foldcase,
                (int (*)(void*,void*))(strcmp));


        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* maximum length of input string */
int _getline(char *s, int lim);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
    clock_t start, end;
    start = clock();
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete end of string */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    end = clock();
    printf("readlines with alloc: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return nlines;
}

/* writelines: output strings into out stream */
void writelines(char *lineptr[], int nlines)
{
    //int i;
    //for (i = 0; i < nlines; i++)
    //    printf("%s\n", lineptr[i]);
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

int _getline(char *s, int lim)
{
    int c;
    char *sStart = s;

    while (--lim > 0 && (c=getchar ()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - sStart;
}

/* qsort: sort v[left]..v[right] in desired order */
void _qsort(void *v[], int left, int right,
        int reverse, int foldcase,
        int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int i, int j);
    char s1[MAXLEN], s2[MAXLEN];
    
    void mytolower(char *destination, char *source);

    if (left >= right) /* do nothing if in array less than two elements */
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        char *vi = v[i], *vleft = v[left];

        if (foldcase) {
            mytolower(s1, vi), mytolower(s2, vleft);
            vi = s1, vleft = s2;
        }
            
        if (reverse && ((*comp)(vi, vleft) > 0))
            swap(v, ++last, i);
        else if (!reverse && ((*comp)(vi, vleft) < 0))
            swap(v, ++last, i);
    }
    swap(v, left, last);
    _qsort(v, left, last-1, reverse, foldcase, comp);
    _qsort(v, left+1, right, reverse, foldcase, comp);
}

int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    return v1 - v2;
}


int dircmp(char *s1, char *s2)
{
    char a, b;
    do {
        while (!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
            s1++;
        while (!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
            s2++;
        a = *s1++;
        b = *s2++;

        if ( a == b && a == '\0')
            return 0;
    } while (a == b);
    return a - b;
}

void swap(void *v[], int i, int j)
{
    void *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

