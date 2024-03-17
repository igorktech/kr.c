#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tnode.h"

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *, int *);
void treeprint(struct tnode *);
void arrprint(struct tnode **, int);
int getword(char *, int);
int isnoise(char *);

void _qsort(void *[], int, int, int,
        int (*comp)(void *, void *));
int nodecmp(struct tnode *, struct tnode *);

int tree_to_array(struct tnode **, struct tnode *, int);

void free_tree(struct tnode *);

/* count word frequency */
int main()
{
    struct tnode *root;
    char word[MAXWORD];
    int word_count = 0;
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, &word_count);
    treeprint(root);
    printf("word count: %d", word_count); 
    struct tnode **array =
        (struct tnode **) malloc(word_count * sizeof(struct tnode *));
    
    tree_to_array(array, root, 0);
    _qsort((void **)array, 0, word_count-1, 1,
                (int (*)(void*,void*))(nodecmp));
    arrprint(array, word_count);

    free_tree(root);
    free(array);
    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/* addtree: add new node with word w into node p or lower */
struct tnode *addtree(struct tnode *p, char *w, int *wc)
{
    int cond;

    if (p == NULL) {    /* new word */
        p = talloc();   /* create new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        (*wc)++;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;     /* count word */
    else if (cond < 0)  /* lower - left subtree */
        p->left = addtree(p->left, w, wc);
    else
        p->right = addtree(p->right, w, wc);
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

void arrprint(struct tnode ** arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%4d %s\n", arr[i]->count, arr[i]->word);
}

int isnoise(char *w) 
{
    static char *noise[] =
    {
        "a",
		"an",
		"and",
		"are",
		"for",
		"from",
		"in",
		"is",
		"it",
		"not",
		"of",
		"on",
		"or",
		"that",
		"the",
		"this",
		"to",
		"was",
		"with"
    };

    int left = 0;
    int right = sizeof(noise) / sizeof(char *) - 1;
    int mid;
    int cond;
    while (left <= right)
    {
        mid = (right + left) / 2;
        
        if((cond = strcmp(w, noise[mid]) == 0))
                return 1;
        else if (cond < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return 0;

}

/* qsort: sort v[left]..v[right] in increasing order */
void _qsort(void *v[], int left, int right, int reverse,
        int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right) /* do nothing if in array less than two elements */
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (reverse && ((*comp)(v[i], v[left])> 0))
            swap(v, ++last, i);
        else if (!reverse && ((*comp)(v[i], v[left])< 0))
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last-1, reverse, comp);
    _qsort(v, left+1, right, reverse, comp);
}

int nodecmp(struct tnode *n1, struct tnode *n2)
{

    if (n1->count < n2->count)
        return -1;
    else if (n1->count > n2->count)
        return 1;
    return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int tree_to_array(struct tnode ** arr, struct tnode * node, int idx)
{
    if (!node)
        return idx;

    arr[idx++] = node;
    idx = tree_to_array(arr, node->left, idx);
    return tree_to_array(arr,node->right, idx);
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

