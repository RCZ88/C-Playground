//
// Created by clementzhao on 15/10/2026.
//

#ifndef LEARN_ABC_LINKEDLIST_H
#define LEARN_ABC_LINKEDLIST_H

//
// Created by clementzhao on 15/10/2026.
//

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
    void *val;
    struct Node *next;
    struct Node *prev;
} Node;

typedef enum {
    INT = 0,
    STRING = 1,
    CHAR = 2,
    DOUBLE = 3
} Type;

typedef int (*CompareFn)(const void *a, const void *b, Type type);
typedef void (*ForEachFn)(void *value, Type type, void *user_data);
typedef bool (*PredicateFn)(const void *value, Type type, void *user_data);

/* Allocation helper used by the implementation. */
typedef struct AllocationResult {
    void *heap;
} AllocationResult;

AllocationResult callocc(size_t count, size_t size, int line);

Node *initNode(void *value, Node *next, Node *prev);

/* Traversal */
Node getTailNode(Node *node);
void *getTail(Node *node);

Node getHeadNode(Node *node);
void *getHead(Node *node);

int getSize(Node *node);
bool isEmpty(Node *node);

/* Insertion */
void insertTail(void *val, Node *node);
void insertHead(void *val, Node *node);
void insertMiddle(void *val, Node *node, Type type);

void insertAt(void *val, Node *node, int index);
void insertAfter(Node *node, void *val);
void insertBefore(Node *node, void *val);

/* Search */
Node *find(void *val, Node node, Type type);
Node *findAt(Node *node, int index);
int indexOf(void *val, Node *node, Type type);
bool contains(void *val, Node *node, Type type);

/* Removal */
void removeVal(void *val, Node *node, Type type);

inline void removeAt(Node *node, int index) {
}

void removeHead(Node *node);
void removeTail(Node *node);
void clear(Node *node);

/* Update */
void setAt(Node *node, int index, void *val);
void *getAt(Node *node, int index);

/* Sorting and reversal */
void sort(Node *node, Type type);
void reverse(Node *node);

/* Copying and conversion */
Node *copyList(Node *node);
void **toArray(Node *node, int *outSize);

/* Functional-style operations */
void forEach(Node *node, ForEachFn callback, void *user_data);
Node *filter(Node *node, PredicateFn predicate, void *user_data);
bool any(Node *node, PredicateFn predicate, void *user_data);
bool every(Node *node, PredicateFn predicate, void *user_data);

/* Utility */
void printList(Node *node, Type type);
void swapNodes(Node *a, Node *b);
void freeList(Node *node);

#endif //LEARN_ABC_LINKEDLIST_H
