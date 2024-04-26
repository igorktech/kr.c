#include <stdio.h>
#include <ctype.h>
#include <string.h>

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

int upper(int c) {
    return (c >= 'a' && c <= 'z') ? c + ('A' - 'a') : c;
}

enum caseType {NOT_DEFINED = -1, UPPER, LOWER};
enum caseType get_case(char *s);

int main (int argc, char *argv[])
{
    int c;
    enum caseType type = get_case(argv[0]);

    if (type == NOT_DEFINED)
        return -1;

    while ((c = getchar()) != EOF) {
        if (type == UPPER)
            putchar(toupper(c));
        else if (type == LOWER)
            putchar(tolower(c));
    }
    return 0;
}

enum caseType get_case(char *s)
{
    if (strstr(s, "toupper") != NULL)
        return UPPER;
    if (strstr(s, "tolower") != NULL)
        return LOWER;
    return NOT_DEFINED;
}
