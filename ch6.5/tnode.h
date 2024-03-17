struct tnode {              /* node of the tree: */
    char *word;             /* pointer to the word */
    int count;              /* usage frequency */
    struct tnode *left;     /* left child node */
    struct tnode *right;    /* right child node */
};


