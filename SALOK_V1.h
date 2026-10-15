//
// Created by clementzhao on 15/10/2026.
//

#ifndef LEARN_ABC_SALOK_V1_H
#define LEARN_ABC_SALOK_V1_H
//
// Created by clementzhao on 13/10/2026.
//

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct {
    void* heap;
    size_t size;
    const char* filename;
    int line;
    int index;
    bool freed;
}HeapMD;

static HeapMD *heaps;
static int count =0;
static uint32_t cap;
static char *FILENAME;

static void handleFull();
static void initHeaps(uint32_t capacity, char * fileName);
static HeapMD callocc(uint32_t amount, size_t size, int line);
static HeapMD reallocc(void* ptr, size_t size, int line);
static void freee();
static void freeOne(int line);

#endif //LEARN_ABC_SALOK_V1_H
