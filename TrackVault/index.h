//
// Created by clementzhao on 21/09/2026.
//

#ifndef LEARN_ABC_INDEX_H
#define LEARN_ABC_INDEX_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "arena.h"


typedef struct {
    uint32_t *keys;     /* track IDs            */
    uint32_t *vals;     /* position in tracks[] */
    size_t    cap;      /* power of two, ≥ 16   */
    size_t    count;
    size_t    probe_total;  /* instrumentation for stats */
    Arena     arena;
} IdIndex;

void   index_init(size_t capacity, IdIndex *ix);
bool   index_insert(IdIndex *ix, uint32_t id, uint32_t pos); /* false: duplicate or OOM */
bool   index_find(const IdIndex *ix, uint32_t id, uint32_t *pos_out);
void   index_destroy(IdIndex *ix);
double index_load_factor(const IdIndex *ix);

#endif //LEARN_ABC_INDEX_H
