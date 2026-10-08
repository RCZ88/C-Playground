//
// Created by clementzhao on 22/09/2026.
//


#include <stdint.h>
#include <string.h>

#include "library.h"
#include "flags.h"

/***

Offset  0: [ id           ] (4 bytes: uint32_t)
Offset  4: [ flags        ] (1 byte : packed TrackFlags)
Offset  5: [ rating       ] (1 byte : uint8_t)
Offset  6: [ duration_sec ] (4 bytes: uint32_t)
Offset 10: [ year         ] (2 bytes: uint16_t)
Offset 12: [ title_len    ] (2 bytes: uint16_t)
Offset 14: [ title_offset ] (4 bytes: uint32_t)
Offset 18: [ artist_len   ] (2 bytes: uint16_t)
Offset 20: [ artist_off   ] (4 bytes: uint32_t)

 ***/

void record_pack(const Track *t, uint32_t title_off, uint32_t artist_off, uint8_t out[24]) {
    put_le(t->id, out, sizeof(t->id));
    uint8_t flagsBit;
    flags_pack(&t->flags, &flagsBit);
    put_le(flagsBit, out+4, sizeof(t->flags));
    put_le(t->rating, out+5, sizeof(t->rating));
    put_le(t->duration_sec, out+6, sizeof(t->duration_sec));
    put_le(t->year, out+10, sizeof(t->year));
    put_le(strlen(t->title)+2, out+12, 2);
    put_le(title_off, out+14, sizeof(title_off));
    put_le(strlen(t->artist)+2, out+18, 2);
    put_le(artist_off, out+20, sizeof(title_off));
}


void record_unpack(const uint8_t in[24],
                   Track *t,
                   const uint16_t *title_len,
                   const uint32_t *title_off,
                   const uint16_t *artist_len,
                   const uint32_t *artist_off) {
    memcpy(&t->id, in, sizeof(t->id));
    uint8_t flagsInt = in[4];
    TrackFlags flags;
    flags_unpack(flagsInt, &flags);
    t->flags = flags;
    t->rating = in[5];
    memcpy(&t->duration_sec, in+6, sizeof(t->duration_sec));
    memcpy(&t->year, in+10, sizeof(t->year));
    memcpy(&t->title, in+*title_off, *title_len);
    memcpy(&t->artist, in+*artist_off, *artist_len);

    
}