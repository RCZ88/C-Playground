//
// Created by clementzhao on 11/10/2026.
//

#ifndef LEARN_ABC_HEAPTREE_H
#define LEARN_ABC_HEAPTREE_H

typedef struct  {
    int *nums;
}HeapTree;

HeapTree initHeap(int size);
int removeAt(int index);
int removeMin();
void insert(HeapTree *ht, int val);


#endif //LEARN_ABC_HEAPTREE_H
