#include <stdio.h>
void *mymalloc(unsigned nbytes);
void *mycalloc(unsigned n, size_t size);
void myfree(void *ap);
void bfree(void *p, unsigned n);

typedef long Align;

union header {
    struct {
        union header *ptr; /*pointer to next block */
        unsigned size;     /* size of block */
    } s;
    Align x; /* force alignment */
};

typedef union header Header;

int main() {
    int *array;
    int n, i;
    n = 10;
    array = (int *)mymalloc(n * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        array[i] = i + 1;

    printf("array elements: ");
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n");
    myfree(array);
    printf("malloc allocated memory successfully\n");

    array = mycalloc(1000, sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 1000; i++)
        if (array[i] != 0) {
            fprintf(stderr,
                    "error: calloc failed to initialize memory to zero\n");
            myfree(array);
            return -1;
        }
    myfree(array);
    printf("calloc allocated memory successfully\n");

    char *p = NULL, phdr[sizeof(Header)], phdr2[sizeof(Header) * 2];

    printf("checking border cases\n");

    printf("bfree NULL ptr\n");
    bfree(p, sizeof(p));

    printf("bfree sizeof(Header) ptr\n");
    bfree(phdr, sizeof(phdr));

    printf("bfree sizeof(Header)*2 ptr\n");
    bfree(phdr2, sizeof(phdr2));

    printf("check malloc dummy variable\n");
    char *dummy = mymalloc(sizeof(Header));
    dummy[0] = '!';

    printf("check free dummy variable\n");
    myfree(ddummy);

    return 0;
}
