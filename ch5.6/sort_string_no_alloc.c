#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000 /* maximum number of strings to sort */

char *lineptr[MAXLINES]; /* ponters to strings */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort( char *lineptr[], int left, int right);

int main()
{
    int nlines; /* number of inserted srtings */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* maximum length of input string */
#define BUFFER_SIZE 1000000

char buffer[BUFFER_SIZE];

int _getline(char *s, int lim);

int readlines(char *lineptr[], int maxlines)
{
    clock_t start, end;
    start = clock();
    int len, nlines;
    char *p = buffer, line[MAXLEN];
    
    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p + len > buffer + BUFFER_SIZE))
            return -1;
        else {
            line[len-1] = '\0'; /* delete end of string */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    end = clock();
    printf("readlines without alloc: %f\n",
            ((double)(end - start)) / CLOCKS_PER_SEC);
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

/* qsort: sort v[left]..v[right] in increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing if in array less than two elements */
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, left+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

