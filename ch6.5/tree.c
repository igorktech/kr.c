#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tnode.h"

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void free_tree(struct tnode *);
/* count word frequency */
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);

    free_tree(root);

    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/* addtree: add new node with word w into node p or lower */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* new word */
        p = talloc();   /* create new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;     /* count word */
    else if (cond < 0)  /* lower - left subtree */
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: print tree p in alphabetic order */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

void free_tree(struct tnode *node)
{
    if(!node)
        return;

    free(node->word);
    free_tree(node->left);
    free_tree(node->right);

    free(node);
}

