//
// Created by clementzhao on 19/09/2026.
//

#ifndef LEARN_ABC_FLAGS_H
#define LEARN_ABC_FLAGS_H
#include <stdbool.h>
#include <stdint.h>
#include "serialization.h"
#include <stddef.h>
#define FLAG_FAVORITE 1 << 0
#define FLAG_EXPLICIT 1 << 1
#define FLAG_LOSSLESS 1 << 2

typedef struct {
    bool    favorite; //2^1
    uint8_t genre;      /* 0..7   -> 2^3*/
    bool    explicit_;  /* name clash with keyword; your call how to spell it 2^1*/
    uint8_t media;      /* 0..2   -> 2^1*/
    bool    lossless; //2^1
} TrackFlags;

const int TF_FIELDS_COUNT = 5;
FieldMeta trackFlagsFields[] = {
    { .name = "favorite", .offset = offsetof(TrackFlags, favorite), .bitSize = 1},
    {.name = "genre", .offset = offsetof(TrackFlags, genre), .bitSize =  3},
    {.name = "explicit", .offset = offsetof(TrackFlags, explicit_), .bitSize = 1},
    {.name = "media", .offset = offsetof(TrackFlags, media), .bitSize = 1},
    {.name = "lossless", .offset = offsetof(TrackFlags, lossless), .bitSize = 1},
};

static bool check_flag(uint8_t flags, uint8_t mask);
static uint8_t set_flag(uint8_t flags, uint8_t mask);
static uint8_t clear_flag(uint8_t flags, uint8_t mask);


bool flags_pack(const TrackFlags *f, uint8_t *out);   /* false if invalid input */
bool flags_unpack(uint8_t raw, TrackFlags *out);      /* false if media == 3   */


#endif //LEARN_ABC_FLAGS_H

