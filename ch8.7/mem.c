/* #include <stdlib.h> */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

typedef long Align;

union header {
    struct {
        union header *ptr; /*pointer to next block */
        unsigned size;     /* size of block */
    } s;
    Align x; /* force alignment */
};

typedef union header Header;

static Header base;          /* empty list beginning */
static Header *freep = NULL; /* list beginning */

void *mymalloc(unsigned nbytes);
static Header *mymorecore(unsigned nu);
void myfree(void *ap);

/* malloc: function for mem distribution */
void *mymalloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0 || nbytes >= UINT_MAX - sizeof(Header)) {
        fprintf(stderr, "malloc: invalid size requested\n");
        return NULL;
    }

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { /* no list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {   /* enough size */
            if (p->s.size == nunits) /*  exact size */
                prevp->s.ptr = p->s.ptr;
            else { /* cut tail */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) /* points to list */
            if ((p = mymorecore(nunits)) == NULL)
                return NULL; /* no memory */
    }
}

/* calloc: returns initialized with 0 n blocks size size */
void *mycalloc(unsigned n, size_t size) {
    void *ptr;
    unsigned total_size = n * size;
    if ((ptr = mymalloc(total_size)) != NULL)
        memset(ptr, 0, total_size);
    return ptr;
}

#define NALLOC 1024 /* minimal requested number of blocks */

/* morecore: requests more memory from system */
static Header *mymorecore(unsigned nu) {
    char *cp; /*, *sbrk(int);*/
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    /* cp = sbrk(nu * sizeof(Header)); */
    /* if (cp == (char *) -1)  /1* not enough memory *1/ */
    /*     return NULL; */
    cp = mmap(NULL, nu * sizeof(Header), PROT_READ | PROT_WRITE,
              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (cp == MAP_FAILED) /* not enough memory */
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    myfree((void *)(up + 1));
    return freep;
}

/* free: return occupied block ap back into list of free blocks */
void myfree(void *ap) {
    Header *bp, *p;

    if (ap == NULL) {
        fprintf(stderr, "free: NULL pointer passed\n");
        return;
    }

    bp = (Header *)ap - 1; /* pointer to Header */

    if (bp->s.size == 0) {
        fprintf(stderr, "free: 0 units to free\n");
        return;
    }

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* free block is at the beginning or at the end */

    if (bp + bp->s.size == p->s.ptr &&
        bp->s.size + p->s.ptr->s.size < UINT_MAX) { /* upper neighbour */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp &&
        p->s.size + bp->s.size < UINT_MAX) { /* to lower neighbour */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

void bfree(void *p, unsigned n) {
    if (p == NULL)
        fprintf(stderr, "bfree: NULL pointer is not allowed\n");
    else if (n < sizeof(Header) * 2)
        fprintf(stderr, "bfree: provided size is not enough\n");
    else {
        if (freep == NULL) {
            base.s.ptr = freep = &base;
            base.s.size = 0;
        }
        ((Header *)p)->s.size = n / sizeof(Header);
        myfree((void *)p + 1);
    }
}

/* int main() */
/* { */
/*     char *b = mymalloc(0); */
/*     myfree(b); */
/*     myfree(&base); */
/*     myfree(freep); */
/*     return 0; */
/* } */
