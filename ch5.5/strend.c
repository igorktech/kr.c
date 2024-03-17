#include <stdio.h>

int strend(const char *s, const char *t);

int main()
{
    const char *s1 = "abcdef";
    const char *s2 = "def";
    const char *s3 = "xyz";

        printf("%s , %s : %d\n",s1,s2, strend(s1, s2));
        printf("%s , %s : %d\n", s1, s3, strend(s1, s3));
    return 0;
}

int strend(const char *s, const char *t)
{
    const char *sStart = s;
    const char *tStart = t;
    while(*++s);
    while(*++t);

    while((*s-- == *t--) && (s != sStart) && (t != tStart))
        ;

    if (t == tStart)
        return 1;
    return 0;
}

