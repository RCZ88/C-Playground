//
// Created by clementzhao on 19/09/2026.
//

#include "serialization.h"
#include "bytes.h"


void track_serialize(const Track *track, uint8_t *buf) {
    // DynamicInt di_id = (DynamicInt) {
    // .size = SIZE_32, .val = track->id
    // };
    // put_le(di_id, buf);
    // buf += di_id.size;
    for (int i =0; i<TRACK_FIELDS_COUNT; i++) {
        uint8_t *base = (uint8_t *) track + TRACK_FIELDS[i].offset;
        const size_t varSize = TRACK_FIELDS[i].size;
        // put_le(, bytes, varSize);
        for (int  j = 0; j<varSize; j++) {
            get_le((uint64_t)buf, base + j, varSize);
        }
    }
    // *buf <<= track->id;
    // *buf <<= track->duration_sec;
    // *buf <<= track->flags;
}

void track_deserialize(const uint8_t *buf, Track *track) {
    const uint8_t *ptr = buf;

    for (int i = 0; i<TRACK_FIELDS_COUNT; i++) {
        uint8_t *base = (uint8_t *) track + TRACK_FIELDS[i].offset;;
        const size_t varSize = TRACK_FIELDS[i].size;
        uint8_t bytes[varSize];
        put_le((uint64_t)ptr , bytes, varSize);
        for (int j = 0; j<varSize; j++) {
            *(base + j) = bytes[j];
        }
    }
}