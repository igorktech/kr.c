#include <stdio.h>
#define MAX_LEN 1000

void unescape(char* s, char* t);

int main() 
{
    char t[] = "Hello\\n,\\tworld\\!\\v!";
    char s[MAX_LEN];

    printf("%s\n", t);
    unescape(s, t);
    printf("%s\n", s);

    return 0;
}

/* unescape: convert characters to escape sequences*/
void unescape(char* s, char* t) 
{
    int i,j;
    for(i = 0, j = 0; t[i] != '\0'; i++, j++) {
        if (t[i] == '\\' && t[i+1] != '\0'){
            i++;
            switch (t[i]) {
                case 'a':
                    s[j] = '\a';
                    break;
                case 'b':
                    s[j] = '\b';
                    break;
                case 'f':
                    s[j] = '\f';
                    break;
                case 'n':
                    s[j] = '\n';
                    break;
                case 'r':
                    s[j] = '\r';
                    break;
                case 't':
                    s[j] = '\t';
                    break;
                case 'v':
                    s[j] = '\v';
                    break;
                default:
                    s[j++] = '\\';
                    s[j] = t[i];
                    break;
            }
        }
        else
            s[j] = t[i];

    }
    s[j] = '\0';
}
