//
// Created by clementzhao on 11/10/2026.
//


#include <stdlib.h>
#include "HeapTree.h"
#include <math.h>
#include <stdint.h>


HeapTree initHeap(int size) {
    return (HeapTree){
        .nums = calloc(size, sizeof(int))
    };
}

void insert(HeapTree *ht, int val) {
    
}

int gLeft(int i){
    return 2 * i + 1;
}
int gRight(int i ){
    return 2 * i + 2;
}

int getParent(uint8_t i) {
    return (int) floor(((double)i-1) / 2);
}