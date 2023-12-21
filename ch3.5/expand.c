#include <stdio.h>

#define MAX_LEN 1024
void expand(char s1[], char s2[]);

int main()
{
    char s1[] = "-a-z-A-Z-0-9-abcdefaf-3-3-3-6a-ZZ-A-F-J-T-Z\n-a-b ---z 0-9 a-d-f    -1-2! HELLO 0-0 10-3 -";
	char s2[MAX_LEN];
	expand(s1, s2);

	printf("%s\n", s2);

}

void expand(char s1[], char s2[]) 
{
    int i, j, k;

    for (i = 0, j = 0; s1[i]; i++) {
        if (s1[i] == '-' && i > 0 && s1[i] != '\0') {
            int start = s1[i-1];
            int end = s1[i+1];

            if (start < end &&
                    (('a' <= start && end <= 'z') ||
                     ('A' <= start && end <= 'Z') ||
                    ('0' <= start && end <= '9'))) {

                for(;start+1 < end; start++) {
                    s2[j++] = start+1;
                }
            }
            else { 
                s2[j++] = s1[i];
            }
        }
        else {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}
