//
// Created by clementzhao on 15/10/2026.
//


//
// Created by clementzhao on 13/10/2026.
//

//SALOK = SMART MEMORY ALLOCATION
#include "SALOK_V1.h"



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


