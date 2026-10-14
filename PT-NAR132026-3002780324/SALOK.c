//
// Created by clementzhao on 13/10/2026.
//

//SALOK = SMART MEMORY ALLOCATION
#include "SALOK.h"


static void handleFull() {
    if (count >= cap) {
        heaps = realloc(heaps, cap*2);
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

static void initHeaps(const uint32_t capacity, char * fileName) {
    heaps = (HeapMD*)calloc(capacity, sizeof(HeapMD));
    FILENAME = fileName;
    cap = capacity * sizeof(HeapMD);
}

static HeapMD callocc(const uint32_t amount, const size_t size, const int line) {
    void *ptr = calloc(amount, size);
    const size_t total = size * amount;
    handleFull();
    heaps[count] = (HeapMD){
        .heap = ptr,
        .size = total,
        .filename = FILENAME,
        .line = line,
        .index = count,
        .freed = false
    };
    count++;
    return heaps[count-1];
}

static HeapMD reallocc(void* ptr, const size_t size, const int line) {
    void* new_ptr = realloc(ptr, size);
    handleFull();
    heaps[count] = (HeapMD){
        .heap = new_ptr,
        .size = size,
        .filename = FILENAME,
        .line = line,
        .index = count,
        // .freed = false
    };
    count++;
    return heaps[count-1];
}

static bool linSearch(void *key, void *foundArr[], int foundCount) {
    for (int i = 0; i < foundCount; i++) {
        if (foundArr[i] == key) {
            return true;
        }
    }
    return false;
}

static void freee() {
    void *foundArr[count];
    int foundCount = 0;

    for (int i = 0; i < count; i++) {
        if (!linSearch(heaps[i].heap, foundArr, foundCount)) {
            foundArr[foundCount++] = heaps[i].heap;
            free(heaps[i].heap);
        }
    }

    free(heaps);
}

static void freeOne(const int line) {
    for (int i = 0; i<count; i++) {
        if (heaps[i].line == line) {
            free(heaps[i].heap);
            heaps[i].freed = true;
            break;
        }
    }
}

