//
// Created by clementzhao on 21/09/2026.
//

#include "index.h"

#include <stdlib.h>

#include "arena.h"

//

// typedef struct {
//     uint32_t *keys;     /* track IDs            */
//     uint32_t *vals;     /* position in tracks[] */
//     size_t    cap;      /* power of two, ≥ 16   */
//     size_t    count;
//     size_t    probe_total;  /* instrumentation for stats */
// } IdIndex;

// bool   index_insert(IdIndex *ix, uint32_t id, uint32_t pos); /* false: duplicate or OOM */
// bool   index_find(const IdIndex *ix, uint32_t id, uint32_t *pos_out);
// void   index_destroy(IdIndex *ix);
// double index_load_factor(const IdIndex *ix);

uint32_t hash(const uint32_t id, const size_t capacity) {
    size_t mask = capacity - 1;
    //32 bit num. hence using hte pow 2 mod trick.
    return (id * 265443561u) & mask;
}

void index_init(const size_t capacity, IdIndex *ix) {
    ix = calloc(1, sizeof(IdIndex));
    ix->arena = *arena_create(capacity);
    ix->keys = arena_calloc(&ix->arena, capacity, sizeof(uint32_t));
    ix->vals = arena_calloc(&ix->arena, capacity, sizeof(uint32_t));
    ix->cap = capacity;
    ix->count = 0;
    ix->probe_total = 0;
}

//converts id of track into index to find track in arr of tracks.
bool index_find(const IdIndex *ix, const uint32_t id, uint32_t *pos_out) {
    if (ix == NULL || id == 0 || pos_out == NULL) {
        return false;
    }

    uint32_t slot = hash(id, ix->cap);
    uint32_t key = ix->keys[slot];
    if (key == 0) {
        return false;
    }

    if (key == id) {
        *pos_out = ix->vals[slot];
    }else {
        while (key != id) {
            unsigned int mask = ix->cap - 1;
            slot = (slot + 1) & mask;
            key = ix->keys[slot];
            if (key == 0) {
                return false;
            }
        }
        *pos_out = ix->vals[slot];
    }
    return true;
}
//

bool index_insert(IdIndex *ix, uint32_t id, uint32_t pos) {
    if (index_find(ix, id, &pos)) {
      return false;
    }

    unsigned int slot = hash(id, ix->cap);
    uint32_t probes = 0;
    while (ix->keys[slot] != 0) {
        if (ix->keys[slot] == id) {
            return false;
        }
        probes++;
        uint16_t mask = ix->cap - 1;
        slot = (slot + 1) & mask;
    }
    ix->vals[slot] = pos;
    ix->keys[slot] = id;
    ix->count++;
    ix->probe_total += probes;

    return true;
}

void index_destroy(IdIndex *ix) {
    free(ix->keys);
    free(ix->vals);
    ix->keys = NULL;
    ix->vals = NULL;
    ix->count = 0;
    ix->cap = 0;
    free(ix);
}

double index_load_factor(const IdIndex *ix) {
    if (ix == NULL || ix->cap ==0) {
        return 0.0;
    }

    return (double)ix->count / (double)ix->cap;
}

