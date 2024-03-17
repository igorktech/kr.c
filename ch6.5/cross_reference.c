#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXLINES 10

struct tnode {              /* node of the tree: */
    char *word;             /* pointer to the word */
    int lines[MAXLINES];
    struct tnode *left;     /* left child node */
    struct tnode *right;    /* right child node */
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int mygetword(char *, int);
int isnoise(char *);
void free_tree(struct tnode *);

/* count word frequency */
int main()
{
    struct tnode *root;
    char word[MAXWORD];
    unsigned int line = 0;
    int cond;
    root = NULL;
    while ((cond = mygetword(word, MAXWORD)) != EOF && line < MAXLINES) {
        if (cond == '\n') {
            line++;
        }
        else if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, line);
    }
    treeprint(root);

    free_tree(root);

    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/* addtree: add new node with word w into node p or lower */
struct tnode *addtree(struct tnode *p, char *w, int line)
{
    int cond;

    if (p == NULL) {    /* new word */
        p = talloc();   /* create new node */
        p->word = strdup(w);
        for (int i = 0; i < MAXLINES; i++)
            p->lines[i] = 0;
        p->lines[line] = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->lines[line] = 1;     /* flag line */
    else if (cond < 0)  /* lower - left subtree */
        p->left = addtree(p->left, w, line);
    else
        p->right = addtree(p->right, w, line);
    return p;
}

/* treeprint: print tree p in alphabetic order */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s ", p->word);
        for (int i = 0; i < MAXLINES; i++)
            printf("%d ", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

int mygetword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n') {
            *w = '\0';  // Terminate the word
            return c;   // Return newline character
        }    

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
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

    /* int lenght = sizeof(noise) / sizeof(char *); */
        
    /* for(int i = 0; i < length; i++) */
    /*     if (!strcmp(w, noise[i]) */
    /*             return 1; */
    /* return 0; */

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

void free_tree(struct tnode *node)
{
    if(!node)
        return;

    free(node->word);
    free_tree(node->left);
    free_tree(node->right);

    free(node);
}

