#include <stdio.h>
#define MAX_LEN 1000

void escape(char* s, char* t);

int main() 
{
    char t[] = "Hello\n,\tworld\\!\v!";
    char s[MAX_LEN];

    printf("%s\n", t);
    escape(s, t);
    printf("%s\n", s);

    return 0;
}

/* escape: convert escape sequences to characters */
void escape(char* s, char* t) 
{
    int i,j;
    for(i = 0, j = 0; t[i] != '\0'; i++, j++) {
        switch (t[i]) {
            case '\a':
                s[j++] = '\\';
                s[j] = 'a';
                break;
            case '\b':
                s[j++] = '\\';
                s[j] = 'b';
                break;
            case '\f':
                s[j++] = '\\';
                s[j] = 'f';
                break;
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\r':
                s[j++] = '\\';
                s[j] = 'r';
                break;
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            case '\v':
                s[j++] = '\\';
                s[j] = 'v';
                break;
            default:
                s[j] = t[i];
                break;
        }
    }
    s[j] = '\0';
}
