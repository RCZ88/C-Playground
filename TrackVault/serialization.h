//
// Created by clementzhao on 19/09/2026.
//

#ifndef LEARN_ABC_TRACK_H
#define LEARN_ABC_TRACK_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "bytes.h"
#include "library.h"

#define TRACK_SERIALIZED_SIZE 7 // 4 bytes (id) + 2 bytes (duration) + 1 byte (flags)


// 1. File Header (12 Bytes Serialized)
typedef struct {
    uint32_t magic;        // 4 bytes: "MLDB" validation
    uint16_t version;      // 2 bytes: Format schema version
    uint16_t reserved;     // 2 bytes: Zero-padded alignment
    uint32_t record_count; // 4 bytes: Number of tracks in file
} Header;

// 3. Index Table Entry (10 Bytes Serialized)
typedef struct {
    uint32_t track_id;     // 4 bytes: Lookup key
    uint32_t file_offset;  // 4 bytes: Byte offset from start of file
    uint16_t record_size;  // 2 bytes: Total length of track data block
} IndexEntry;

typedef struct {
    const char *name;
    size_t offset;
    size_t size;
    uint32_t bitSize;
} FieldMeta;

typedef struct {
    uint32_t track_id;     // 4 bytes: Associated track ID
    uint16_t title_len;    // 2 bytes: Byte count of UTF-8 title string
    uint16_t artist_len;   // 2 bytes: Byte count of UTF-8 artist string
    uint16_t album_len;    // 2 bytes: Byte count of UTF-8 album string
} TagHeader;

// 5. File Integrity Footer (8 Bytes Serialized)
typedef struct {
    uint32_t checksum;     // 4 bytes: CRC32 of preceding file contents
    uint32_t magic_eof;    // 4 bytes: "ENDM" marker
} Footer;

// Define field metadata manually once
const FieldMeta TRACK_FIELDS[] = {
    { .name = "id", .offset = offsetof(Track, id), .size = SIZE_32 },
    { .name = "duration_sec", .offset = offsetof(Track, duration_sec), .size = SIZE_16 },
    { .name = "flags", .offset = offsetof(Track, flags), .size = SIZE_8 }

};

const FieldMeta INDEX_ENTRY_FIELDS[] = {
    { .name = "track_id",     .offset = offsetof(IndexEntry, track_id),     .size = SIZE_32 },
    { .name = "file_offset",  .offset = offsetof(IndexEntry, file_offset),  .size = SIZE_32 },
    { .name = "record_size",  .offset = offsetof(IndexEntry, record_size),  .size = SIZE_16 }
};

// 2. Dynamic String / Metadata Section (Variable Length Strings)
const FieldMeta TAG_HEADER_FIELDS[] = {
    { .name = "track_id",     .offset = offsetof(TagHeader, track_id),     .size = SIZE_32 },
    { .name = "title_len",    .offset = offsetof(TagHeader, title_len),    .size = SIZE_16 },
    { .name = "artist_len",   .offset = offsetof(TagHeader, artist_len),   .size = SIZE_16 },
    { .name = "album_len",    .offset = offsetof(TagHeader, album_len),    .size = SIZE_16 }
};

// 3. File Footer Section (Integrity Validation)
const FieldMeta FOOTER_FIELDS[] = {
    { .name = "checksum",     .offset = offsetof(Footer, checksum),     .size = SIZE_32 },
    { .name = "magic_eof",    .offset = offsetof(Footer, magic_eof),    .size = SIZE_32 }
};

const uint8_t TRACK_FIELDS_COUNT = sizeof(TRACK_FIELDS)/sizeof(FieldMeta);

void track_serialize(const Track *track, uint8_t *buf);
void track_deserialize(const uint8_t *buf, Track *track);

#endif //LEARN_ABC_TRACK_H
