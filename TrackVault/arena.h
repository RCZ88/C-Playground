//
// Created by clementzhao on 20/09/2026.
//

#ifndef LEARN_ABC_ARENA_H
#define LEARN_ABC_ARENA_H
#include <stddef.h>
#include <stdint.h>
#define ARENA_TRACK_CAPACITY  1 << 12

typedef struct {
    size_t capacity, used; //bytes
    size_t alloc_count;
    size_t requested_bytes;   /* sum of raw sizes asked for   */
    size_t aligned_bytes;     /* sum after 8-byte alignment   */
} ArenaStats;



typedef struct {
    uint8_t *buffer;

    size_t   capacity;        // Max capacity
    size_t   used;            // Current bump pointer offset

    // Internal counters needed to populate ArenaStats later
    size_t   alloc_count;     // Number of valid arena_alloc calls
    size_t   requested_bytes; // Unaligned raw sizes requested by user
    size_t   aligned_bytes;   // Post-padding sizes actually consumed
}Arena;


Arena *arena_create(size_t capacity);
void  *arena_alloc(Arena *a, size_t size);          /* NULL when full/invalid */
void  *arena_calloc(Arena *a, size_t count, size_t size); /* overflow-checked, zeroed */
void   arena_reset(Arena *a);                       /* used = 0; all old pointers dangle */
void   arena_destroy(Arena *a);
void   arena_stats(const Arena *a, ArenaStats *out);

#endif //LEARN_ABC_ARENA_H
