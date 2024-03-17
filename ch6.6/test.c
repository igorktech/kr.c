#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int undef(char *name);

int main() {
    char *stringValue = "Hello, World!";
    struct nlist *result;

    result = install("integer", "42");
    if (result == NULL)
        printf("Do not install pair\n");

    result = install("float", "3.14");
    if (result == NULL)
        printf("Do not install pair\n");

    result = install("string", stringValue);
    if (result == NULL)
        printf("Do not install pair\n");


     struct nlist *np;

    for (np = hashtab[hash("string")]; np != NULL; np = np->next)
        printf("%s\n", np->name);

    result = lookup("integer");
    if (result != NULL)
        printf("Integer value: %s\n", (char *)result->defn);

    result = lookup("float");
    if (result != NULL)
        printf("Float value: %s\n", (char *)result->defn);
    
    result = lookup("string");
    if (result != NULL)
        printf("String value: %s\n", (char *)result->defn);

    undef("string");
    result = lookup("string");
    if (result == NULL)
        printf("Pair erased\n");
 
    return 0;
}
