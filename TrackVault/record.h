//
// Created by clementzhao on 22/09/2026.
//

#ifndef LEARN_ABC_RECORD_H
#define LEARN_ABC_RECORD_H
#include "library.h"


void record_pack(const Track *t, uint32_t title_off, uint32_t artist_off, uint8_t out[24]);

void record_unpack(const uint8_t in[24],
                   Track *t,
                   const uint16_t *title_len,
                   const uint32_t *title_off,
                   const uint16_t *artist_len,
                   const uint32_t *artist_off);

#endif //LEARN_ABC_RECORD_H
