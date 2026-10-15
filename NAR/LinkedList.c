//
// Created by clementzhao on 15/10/2026.
//

#include <stddef.h>
#include <string.h>

#include "../SALOK_V1.h"

typedef struct Node{
    void *val;
    struct Node *next;
    struct Node *prev;
}Node;


Node getTailNode(Node *node) {
    if (node->next == NULL) {
        return  *node;
    }
    return getTailNode(node->next);
}

void* getTail(Node *node) {
    return getTailNode(node).val;
}

Node getHeadNode(Node *node) {
    if (node->prev != NULL) {
        return *node;
    }
    return getHeadNode(node->prev);
}

void* getHead(Node *node) {
    return getHeadNode(node).val;
}

void insertTail(void* val, Node *node) {
    Node ln = getTailNode(node);
    ln.next = callocc(1, sizeof(Node), __LINE__).heap;
    Node n = (Node){
        .val = val,
        .next = NULL,
        .prev = &ln,
    };
    ln.next = &n;
}

void insertHead(void* val, Node *node) {
    Node ln = getHeadNode(node);
    ln.prev = callocc(1, sizeof(Node), __LINE__).heap;
    Node n = (Node){
    .val = val,
    .next = &ln,
    .prev = NULL};
    ln.prev = &n;
}

int getSize(Node *node) {
    Node ln = getHeadNode(node);
    int c = 0;
    while (ln.next != NULL) {
        ln = *ln.next;
        c++;
    }
    return c;
}

typedef enum {
    INT = 0,
    STRING = 1,
    CHAR = 2,
    DOUBLE = 3,
}Type;

Node *find(void *val, Node node, Type type) {
    Node ln = getHeadNode(&node);
    while (ln.next != NULL) {
        switch (type) {
            case INT:
                if (*(int *)ln.val == *(int *)val) {
                    return &ln;
                }
                break;
            case STRING:
                if (*(char **)ln.val == *(char **)val) {
                    return &ln;
                }
                break;
            case CHAR:
                if (*(char *)ln.val == *(char *)val) {
                    return &ln;
                }
                break;
            case DOUBLE:
                if (*(double *)ln.val == *(double *)val) {
                    return &ln;
                }
                break;
        }

        ln = *ln.next;
    }
    return NULL;
}

void insertMiddle(void *val, Node *node, Type type) {
    bool condition = false;
    while (!condition && node->next != NULL) {
        switch (type) {
            case INT:
                condition = *(int *)node->next->val < *(int *)val;
                break;
            case DOUBLE:
                condition = *(double *)node->next->val < *(double *)val;
                break;
            case CHAR:
                condition = *(char *)node->next->val < *(char *)val;
                break;
            case STRING:
                condition = strcmp(*(char **)node->next->val, *(char **)val) < 0;
                break;
        }
        if (condition) {
            Node *n = callocc(1, sizeof(Node*), __LINE__).heap;
            n->prev = NULL;
            n->next = NULL;
            n->val = val;
            if (node->prev != NULL) {
                n->prev = node;
                node->next = n;

            }
            if (node->next != NULL) {
                node->next->prev = n;
                n->next = node->next;
            }
            return;
        }
        node = node->next;
    }
}

void remove(void *val, Node *node, Type type) {
    Node *toRemove = find(val, *node, type);
    if (toRemove != NULL) {
        toRemove->prev->next = NULL;
        toRemove->next->prev = NULL;
        if (toRemove->next != NULL) {
            toRemove->next->prev = toRemove->prev;
        }
        if (toRemove->prev != NULL) {
            toRemove->prev->next = toRemove->next;
        }
    }
}

bool isEmpty(Node *node) {
    return node->val == NULL;
}



