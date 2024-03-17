#include <string.h>
#include <stdlib.h>
#include "utils.h"

/* hash: create hash for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s !='\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/*lookup: search for s in table hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* element found */
    return NULL; /* element not found */
}

char *mystrdup(char *);

/* install: add record "name+definition"
        (name, defn) into table hashtab 
*/
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  // name not found 
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = mystrdup(name)) == NULL) 
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval]; // if NULL or other pair move it to the end 
        hashtab[hashval] = np; // set new node as head 
    } else      // already exists int table 
        free((void *) np->defn); // delete old definiton 
    if ((np->defn = mystrdup(defn)) == NULL)
        return NULL;
    return np;
}

int undef(char *name)
{
    struct nlist *np1, *np2;
    unsigned hashval = hash(name);

    for (np2 = np1 = hashtab[hashval]; np1 != NULL;
            np2 = np1, np1 = np1->next)
    {
        if (strcmp(name, np1->name) == 0) { /* element found */
            if (np1 == np2) /* head */
                hashtab[hashval] = np1->next;
            else
                np2->next = np1->next;

            free(np1->name); /* delete key */
            free(np1->defn); /* delete definiton */
            free(np1);
            return 1;
        }
    }
    return 0;
}
