//
// Created by clementzhao on 20/09/2026.
//

#include "arena.h"

#include <stdalign.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


Arena *arena_create(size_t capacity) {
    Arena *a = malloc(sizeof(Arena));
    a->capacity = capacity;
    a->buffer = malloc(capacity);
    a->used = 0;
    a->requested_bytes = capacity;
    a->aligned_bytes = alignof(__typeof__(capacity));
    return a;
}
void arena_destroy(Arena *a) {
    free(a->buffer);
    free(a);
}

void *arena_alloc(Arena *a, const size_t size) {
    if (a->used + size > a->capacity) {
        return NULL;
    }
    void *ptr = &a->buffer[a->used];
    a->used += size;
    a->alloc_count++;
    a->requested_bytes += size;
    a->aligned_bytes += alignof(__typeof__(a->buffer));

    return ptr;
}



void *arena_calloc(Arena *a, size_t count, size_t size) {
    size_t total_bytes = count * size;

    if (a->used + total_bytes > a->capacity) {
        return NULL;
    }
    if (count != 0  && total_bytes > SIZE_MAX) {
        return NULL;
    }

    void *ptr = arena_alloc(a, total_bytes);
    if (ptr) {
        memset(ptr, 0, total_bytes); // Wipes all garbage bytes to 0
    }


    return ptr;
}

void arena_reset(Arena *a) {
    a->used = 0;
    a->aligned_bytes = 0;
}

void arena_stats(const Arena *a, ArenaStats *out) {
    out->alloc_count = a->alloc_count;
    out->requested_bytes = a->requested_bytes;
    out->aligned_bytes = a->aligned_bytes;
    out->capacity = a->capacity;
}