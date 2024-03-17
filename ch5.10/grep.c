#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int _getline(char *line, int max);

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if(argc != 2)
        printf("Usage: find pattern\n");
    else
        while (_getline(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}

int _getline(char *line, int max)
{

    int c;
    char *sStart = line;
    while (--max > 0 && (c = getchar()) && c !=EOF && c != '\n')
        *line++ = c;

    if(c == '\n')
        *line++ = '\n';

    *line = '\0';
    return line - sStart;
}
