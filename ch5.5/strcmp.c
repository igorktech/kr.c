#include <stdio.h>

int _strcmp(const char *s,const char *t);

int main()
{
    const char *s1 = "apple";
    const char *s2 = "orange";
    const char *s3 = "apple";

    int res1 = _strcmp(s1, s2);
    int res2 = _strcmp(s1, s3);

    printf("\nCompare %s, %s: %d\n",s1, s2, res1);
    printf("\nCompare %s, %s: %d\n",s1, s3, res2);

    return 0;
}

int _strcmp(const char *s,const char *t)
{
    while(*s++ == *t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}
