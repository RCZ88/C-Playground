//
// Created by clementzhao on 19/09/2026.
//

#include <stdbool.h>
#include <stdint.h>
#include "flags.h"



static bool check_flag(const uint8_t flags, const uint8_t mask) {
    return (flags & mask) != 0;
}

static uint8_t set_flag(const uint8_t flags, const uint8_t mask) {
    return flags | mask;
}

static uint8_t clear_flag(const uint8_t flags, const uint8_t mask) {
    return flags & ~mask;
}

bool flags_pack(const TrackFlags *f, uint8_t *out) {
    if (f == NULL || out == NULL) {
        return false;
    }
    const uint8_t *start = (const uint8_t *)f;
    for (int i = 0; i< TF_FIELDS_COUNT; i++) {
        *out <<=  (uint8_t) (*start + trackFlagsFields[i].offset);
    }
    return true;
}

bool flags_unpack(uint8_t raw, TrackFlags *out) {
    for (int i = TF_FIELDS_COUNT - 1; i >= 0; i--) {
        const uint8_t mask = 1 << trackFlagsFields[i].bitSize;
        uint8_t *correctVarType = (uint8_t *) out;
        correctVarType[trackFlagsFields[i].offset/sizeof(uint8_t)] =  raw & mask;
    }
    return true;
}

