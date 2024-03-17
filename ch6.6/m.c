#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101

struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
struct nlist *undef(char *name);
char *mystrdup(char *s) /* creates string duplicate s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
int main()
{
	install("name", "Trump");
	struct nlist *n = lookup("name");
	if (n != NULL)
		printf("n->defn: %s\n", n->defn);
	else
		printf("n == NULL\n");

	install("name", "Obama");
	lookup("test");

	n = lookup("name");
	printf("n->defn: %s\n", n->defn);

	n = undef("name");
	printf("n->defn: %s\n", n->defn);
	free(n->name);
	free(n->defn);
	free(n);

	n = lookup("name");
	printf("n == NULL: %d\n", n == NULL);

	return 0;
}

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

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  // name not found 
        printf("Try to create new");
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

struct nlist *undef(char *name)
{
	struct nlist *np;

	if ((np = lookup(name)) == NULL)
		return NULL;

	unsigned hashval = hash(name);
	hashtab[hashval] = NULL;

	return np;
}
