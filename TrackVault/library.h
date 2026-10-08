//
// Created by clementzhao on 21/09/2026.
//

#ifndef LEARN_ABC_LIBRARY_H
#define LEARN_ABC_LIBRARY_H
#include <stdint.h>

#include "arena.h"
#include "flags.h"
#include "index.h"



/**
 * Here is the exact byte layout of each of the 3 file sections:

---

### Section 1: File Header (20 Bytes Fixed)

Located at file offset `0`.

```text
Byte Offset   Size    Field          Type          Value / Rule
───────────────────────────────────────────────────────────────────────────────
0..3          4       magic          char[4]       'M', 'L', 'D', 'B' (0x4D4C4442)
4             1       version        uint8_t       Must be 0x01
5             1       reserved       uint8_t       Must be 0x00
6..7          2       count          uint16_t LE   Number of tracks (0..10000)
8..11         4       table_offset   uint32_t LE   Must equal 20
12..15        4       pool_offset    uint32_t LE   Must equal 20 + (24 * count)
16..19        4       pool_size      uint32_t LE   Total bytes in String Pool

```

---

### Section 2: Record Table Entry ($count \times 24$ Bytes Fixed)

Starts at file offset `20`. Contains `count` contiguous 24-byte entries.

```text
Byte Offset   Size    Field          Type          Value / Rule
───────────────────────────────────────────────────────────────────────────────
0..3          4       id             uint32_t LE   Track ID (1..0xFFFFFFFF)
4             1       flags          uint8_t       Bit-packed flags (§6 mask/shift)
5             1       rating         uint8_t       0..100
6..9          4       duration_sec   uint32_t LE   1..86400
10..11        2       year           uint16_t LE   1900..2100
12..13        2       title_len      uint16_t LE   strlen(title) (1..1023)
14..17        4       title_off      uint32_t LE   Byte offset inside String Pool
18..19        2       artist_len     uint16_t LE   strlen(artist) (0..1023)
20..23        4       artist_off     uint32_t LE   Byte offset inside String Pool

```

---

### Section 3: String Pool (`pool_size` Bytes Variable)

Starts at file offset `pool_offset` (`20 + 24 * count`). Total file size equals `pool_offset + pool_size`.

```text
Byte Offset                                Contents
───────────────────────────────────────────────────────────────────────────────
[pool_offset]                              Track 0 Title Bytes  (no '\0')
[pool_offset + title_len]                  Track 0 Artist Bytes (no '\0')
[pool_offset + title_len + artist_len]     Track 1 Title Bytes  (no '\0')
...                                        ...
[pool_offset + pool_size - 1]              Last byte of text payload

```
 *
 *
 * **/

typedef struct {
    uint32_t   id;
    uint8_t    rating;
    uint32_t   duration_sec;
    uint16_t   year;
    TrackFlags flags;
    char      *title;     /* arena-owned, NUL-terminated */ //
    char      *artist;    /* arena-owned, "" when absent */
} Track;

typedef struct {
    Arena  *arena;        /* owns ALL Track memory */ //stores every track here + second section is the title artist.
    Track  *tracks; //stores only the track address on the arena
    size_t  count;
    IdIndex index;        /* built on load/add */
} Library;



bool library_create(Library *lib, size_t arena_capacity);
bool library_add(Library *lib, const Track *t);   /* copies strings into arena */
void       library_free(Library *lib);

#endif //LEARN_ABC_LIBRARY_H
