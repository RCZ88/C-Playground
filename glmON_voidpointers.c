//
// Created by clementzhao on 11/09/2026.
//
/* generic.c — how "libraries" are actually made: void* + size + callbacks. Nothing else.
 * build: gcc -Wall -Wextra -O2 generic.c -o generic && ./generic
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* ===== 1. THE UNIVERSAL INDEXER ==========================================
 * void* has no arithmetic (size unknown). But unsigned char* steps by 1 byte.
 * Element i of ANY array = (char*)base + i*size.
 * This ONE line is how qsort, memcpy, malloc walk "any type".            */
static void *at(void *base, size_t i, size_t size) {
    return (unsigned char *)base + i * size;
}

/* ===== 2. GENERIC SWAP — works on ANY type ============================== */
static void swap(void *a, void *b, size_t size) {
    unsigned char *tmp = malloc(size);   /* raw bytes, type unknown — fine  */
    memcpy(tmp, a, size);
    memcpy(a,  b, size);
    memcpy(b,  tmp, size);
    free(tmp);
}

/* ===== 3. CALLBACKS = the missing "type parameter" ====================== */
typedef int (*Compare)(const void *a, const void *b);

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;   /* cast = put lens on  */
    return (x > y) - (x < y);
}
static int cmp_double(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}

/* ===== 4. OUR OWN GENERIC SORT (same idea as libc qsort) ================ */
static void selection_sort(void *base, size_t n, size_t size, Compare cmp) {
    for (size_t i = 0; i + 1 < n; i++) {
        size_t best = i;
        for (size_t j = i + 1; j < n; j++)
            if (cmp(at(base, j, size), at(base, best, size)) < 0) best = j;
        if (best != i) swap(at(base, i, size), at(base, best, size), size);
    }
}

/* ===== 5. VEC — dynamic array OF void* (your "void* arr[]") ============= */
typedef struct {
    void  **data;    /* heap block: array of slots, each holds ANY pointer */
    size_t  len, cap;
} Vec;

static void vec_init(Vec *v) {
    v->cap = 4; v->len = 0;
    v->data = malloc(v->cap * sizeof(void*));   /* 8 bytes per slot, x86-64 */
}
static void vec_push(Vec *v, void *item) {
    if (v->len == v->cap) {
        v->cap *= 2;
        /* We update v->data through Vec* so the CALLER sees the new block.
         * If vec took Vec BY VALUE, realloc would update only the copy and
         * the caller's v->data would dangle. THIS is the T* vs T** lesson. */
        v->data = realloc(v->data, v->cap * sizeof(void*));
    }
    v->data[v->len++] = item;
}

/* ===== 6. TYPE TAGS — the runtime answer to "what type is this?" ======== */
typedef enum { T_INT, T_DOUBLE, T_CSTR } Type;
typedef struct { Type tag; void *ptr; } Cell;    /* tag travels WITH pointer */

static void cell_print(Cell c) {
    switch (c.tag) {
        case T_INT:    printf("%d",     *(int    *)c.ptr); break;
        case T_DOUBLE: printf("%.2f",   *(double *)c.ptr); break;
        case T_CSTR:   printf("\"%s\"", (char   *)c.ptr); break;
    }
}

/* ===== 7. ARENA — a malloc you can write yourself (bump allocator) ====== */
typedef struct { unsigned char *base, *next, *end; } Arena;

static void arena_init(Arena *a, size_t cap) {
    a->base = malloc(cap);
    a->next = a->base;
    a->end  = a->base + cap;
}
static void *aalloc(Arena *a, size_t size) {    /* returns void* — malloc's job */
    size = (size + 15) & ~(size_t)15;           /* round to 16: ALIGNMENT       */
    if ((size_t)(a->end - a->next) < size) return NULL;
    void *p = a->next;
    a->next += size;                            /* "bump". that's the whole thing */
    return p;
}

int main(void) {
    printf("== A. swap any type ==\n");
    int    a = 1,   b = 2;   swap(&a, &b, sizeof a);
    double x = 1.5, y = 9.9; swap(&x, &y, sizeof x);
    printf("a=%d b=%d | x=%.1f y=%.1f\n", a, b, x, y);

    printf("\n== B. ONE sort function, ANY type ==\n");
    int    ia[] = {5, 3, 8, 1, 9, 2};
    double da[] = {3.3, 1.1, 2.2};
    selection_sort(ia, 6, sizeof(int),    cmp_int);
    selection_sort(da, 3, sizeof(double), cmp_double);
    for (size_t i = 0; i < 6; i++) printf("%d ",  ia[i]);
    printf("| ");
    for (size_t i = 0; i < 3; i++) printf("%.1f ", da[i]);
    printf("\n(identical code — only size + callback differed)\n");

    printf("\n== C. the void** chain: ptr -> [void*] -> [data] ==\n");
    int val = 7;
    void  *pv  = &val;      /* int* -> void*  : implicit, lossless           */
    void **ppv = &pv;       /* address of the CELL that holds the void*      */
    /*   ppv ──▶ pv ──▶ &val ──▶ 7                                           */
    printf("unwrapped: %d\n", *(int *)*ppv);  /* *ppv = void*, cast, deref  */
    /* void** is NOT "pointer to any pointer type". It is exactly
     * "pointer to one void* cell". int** -> void** wholesale is technically
     * UB. Clean pattern — convert per element:
     *     int **ipp = ...;   void *v = ipp[i];   /* implicit, always safe */

    printf("\n== D. Vec of void* holding MIXED types ==\n");
    Vec v; vec_init(&v);
    int    *pi = malloc(sizeof(int));     *pi = 42;
    double *pd = malloc(sizeof(double));  *pd = 2.71;
    vec_push(&v, pi);
    vec_push(&v, pd);
    vec_push(&v, (void *)"idiot");        /* literal address -> void*        */
    Cell cells[3] = { {T_INT, pi}, {T_DOUBLE, pd}, {T_CSTR, (void*)"idiot"} };
    for (size_t i = 0; i < 3; i++) { cell_print(cells[i]); printf(" "); }
    printf("\nlen=%zu cap=%zu slot=%zu bytes\n", v.len, v.cap, sizeof(void*));

    printf("\n== E. Arena: your own malloc ==\n");
    Arena ar; arena_init(&ar, 1024);
    int    *batch = aalloc(&ar, 4 * sizeof(int));   /* void* -> any: no cast */
    double *d     = aalloc(&ar, sizeof(double));    *d = 6.28;
    for (int i = 0; i < 4; i++) batch[i] = i * 10;
    printf("batch: %d %d %d %d | d=%.2f\n", batch[0], batch[1], batch[2], batch[3], *d);
    printf("used %zu of 1024 bytes\n", (size_t)(ar.next - ar.base));
    /* free(ar.base) releases EVERYTHING at once — no per-object frees      */

    free(ar.base); free(pi); free(pd); free(v.data);
    return 0;
}