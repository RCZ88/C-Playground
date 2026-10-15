//
// Created by clementzhao on 13/10/2026.
//

//SALOK = SMART MEMORY ALLOCATION
#include "SALOK_V2.h"



static void *handleFull(void *heap, size_t newSize) {
    return realloc(heap, newSize);
}

static void handleFullStorage() {
    if (count  > cap) {
        heaps = handleFull(heaps, cap * 2);
        cap *= 2;
    }
}
/*
 * Bash Command to Refactor usage:
 * - All Files:
 * perl -pi -e 's/\b(calloc|realloc)\s*\(\s*(.*?)\s*,\s*(.*?)\s*\);/\1c(\2, \3, __LINE__).heap;/g' *.c
 * - Specific File:
 * perl -pi -e 's/\b(calloc|realloc)\s*\(\s*(.*?)\s*,\s*(.*?)\s*\);/\1c(\2, \3, __LINE__).heap;/g' main.c
 * - Multiple Specific Files:
 * perl -pi -e 's/\b(calloc|realloc)\s*\(\s*(.*?)\s*,\s*(.*?)\s*\);/\1c(\2, \3, __LINE__).heap;/g' main.c memory.c helpers.h
 */


//done once
void START_ARR(char *fileName) {
    heaps = (DynamicArr**)calloc(2, sizeof(DynamicArr));
    FILENAME = fileName;
    cap = 2;
}


DynamicArr arr(const uint32_t amount, const size_t size, const int line) {
    void *ptr = calloc(amount, size);
    const size_t total = size * amount;
    handleFullStorage();
    heaps[count] = &(DynamicArr){
        .heap = &ptr,
        .size = total,
        .filename = FILENAME,
        .line = line,
        .index = count,
        .freed = false
    };
    count++;
    return *heaps[count-1];
}

void addItem(DynamicArr *dest, void *item) {
    if (dest->allocated > dest->size) {
        void *newLoc = realloc(*dest->heap, dest->size * 2);
        dest->heap = &newLoc;
    }
    dest->heap[dest->allocated++] = &item;
}

void removeItem(DynamicArr da, int index) {
    if (index < 0) {
        return;
    }
    void *base_ptr = &getDat(da)[index];

}

DynamicArr reallocc(void* ptr, const size_t size, const int line) {
    void* new_ptr = realloc(ptr, size);
    handleFullStorage();
    heaps[count] = &(DynamicArr){
        .heap = new_ptr,
        .size = size,
        .filename = FILENAME,
        .line = line,
        .index = count,
        // .freed = false
    };
    count++;
    return *heaps[count-1];
}

void *getDat(DynamicArr arr) {
    return *arr.heap;
}

bool linSearch(void *key, void *foundArr[], int foundCount) {
    for (int i = 0; i < foundCount; i++) {
        if (foundArr[i] == key) {
            return true;
        }
    }
    return false;
}

void END_ARR() {
    void *foundArr[count];
    int foundCount = 0;

    for (int i = 0; i < count; i++) {
        if (!linSearch(heaps[i]->heap, foundArr, foundCount)) {
            foundArr[foundCount++] = heaps[i]->heap;
            free(heaps[i]->heap);
        }
    }

    free(heaps);
}


void deleteArr(DynamicArr arr) {
    for (int i = 0; i<count; i++) {
        if (heaps[i]->line == arr.line) {
            free(*heaps[i]->heap);
            heaps[i]->freed = true;
            break;
        }
    }
}

