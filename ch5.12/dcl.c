#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;          /* type of the last lexeme */
char token[MAXTOKEN];   /* last inserted lexeme */
char name[MAXTOKEN];    /* name of identificator */
char datatype[MAXTOKEN];/* data type = char, int and etc */
char out[1000];         /* result string */

int main()  /* convert definitions into words */
{
    while (gettoken() != EOF) {     /* 1st lexeme in string - */
        strcpy(datatype, token);    /* data type */
        out[0] = '\0';
        dcl();      /* analysis of the rest part of string */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
/*dcl: syntax analyzer of definiton */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* count * */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* ditdcl: syntax analyzer of direct definition */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') { /* (def) */
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

int gettoken(void)  /* read current lexeme */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}
