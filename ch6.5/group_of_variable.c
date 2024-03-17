#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {              /* node of the tree: */
    char *word;             /* pointer to the word */
    int count;              /* usage frequency */
    struct tnode *left;     /* left child node */
    struct tnode *right;    /* right child node */
};


struct tlist {
    struct tlist *pNext;
    struct tnode *pTree;
};

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void addgroup(struct tlist **, char *, int);

void treeprint(struct tnode *);
void groupprint(struct tlist *);
int getword(char *, int);
int getvariable(char *, int);
int iskeyword(char *);

void free_tree(struct tnode *);
void free_list(struct tlist *);

/* count word frequency */
int main(int argc, char *argv[])
{
    int cond;
    int same_length = 1;
    if(argc > 1)
        same_length = atoi(argv[1]);

    struct tlist *list = NULL;
    char word[MAXWORD];

    while ((cond = getword(word, MAXWORD)) != EOF)
        if (isalpha(word[0]))
            if(iskeyword(word)) {
                if((cond = getvariable(word, MAXWORD)) != EOF){
                    addgroup(&list, word, same_length);
                }
            }
    groupprint(list);

    free_list(list);

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


void addgroup(struct tlist **list, char * w, int same_size)
{
    struct tlist *current = *list;
    struct tlist *prev = NULL;

    // try to find
    while(current != NULL) {
        /* printf("comp %s\n",current->pTree->word); */
        if(strncmp(current->pTree->word,w,same_size)==0) {
            current->pTree = addtree(current->pTree,w);
            return;
        }
        prev = current;
        current = current->pNext;
    }

    struct tlist *node = (struct tlist *)malloc(sizeof(struct tlist));
    node->pNext = NULL;
    node->pTree = addtree(NULL, w); 

    if (prev == NULL) {
        // make the new node the head of the list
        *list = node;
    } else {
        // add the new node to the end of the list
        prev->pNext = node;
    }
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

void groupprint(struct tlist *list)
{
    struct tlist *current = list;

    while (current != NULL) {
        printf("Group:\n");
        treeprint(current->pTree);
        printf("\n");
        current = current->pNext;
    }
}

int getvariable(char *word, int lim) 
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) || c == '*')
        ;
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

int iskeyword(char *w) 
{
    static char *keywords[] = {
        "void", 
        "char", 
        "int", 
        "float", 
        "double"
    };

    int left = 0;
    int right = sizeof(keywords) / sizeof(char *) - 1;
    int mid;
    int cond;
    while (left <= right)
    {
        mid = (right + left) / 2;
        
        if((cond = strcmp(w, keywords[mid]) == 0))
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

void free_list(struct tlist *list)
{
    if(!list)
        return;

    free_tree(list->pTree);
    free_list(list->pNext);

    free(list);
}
