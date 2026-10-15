//
// Created by clementzhao on 13/10/2026.
//

#ifndef LEARN_ABC_SALOK_H
#define LEARN_ABC_SALOK_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
// #define DA_TYPE(T) struct { T *data; size_t length; size_t capacity; }
#define DA_DEFINE(Name, T)                                      \
    typedef struct {                                             \
        DynamicArr inner;                                        \
    } Name;                                                      \
                                                                 \
    static inline bool Name##_init(Name *arr, size_t capacity) { \
        return da_init(&arr->inner, sizeof(T), capacity);        \
    }                                                            \
                                                                 \
    static inline bool Name##_push(Name *arr, T value) {         \
        return da_push(&arr->inner, &value);                     \
    }                                                            \
                                                                 \
    static inline T *Name##_get(Name *arr, size_t index) {       \
        return (T *)da_get(&arr->inner, index);                  \
    }                                                            \
                                                                 \
    static inline void Name##_destroy(Name *arr) {               \
        da_destroy(&arr->inner);                                 \
    }

typedef struct {
    void** heap;
    size_t size;
    size_t allocated;
    const char* filename;
    int line;
    int index;
    bool freed;
}DynamicArr;

static DynamicArr **heaps;
static int count =0;
static uint32_t cap;
static char *FILENAME;

static void* handleFull(void *heap, size_t newSize);
static void START_ARR(char *fileName);
static void addItem(DynamicArr *dest, void *item);
static void *getDat(DynamicArr arr);
static DynamicArr arr(uint32_t amount, size_t size, int line);
static DynamicArr reallocc(void* ptr, size_t size, int line);
static void END_ARR();
static void deleteArr(DynamicArr arr);

#endif //LEARN_ABC_SALOK_H
