struct nlist { /* table record */
    struct nlist *next; /*next record int the chain */
    char *name;         /* name in #define */
    char *defn;         /* substituted text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /*table of pointers */



