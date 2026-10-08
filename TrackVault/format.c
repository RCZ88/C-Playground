//
// Created by clementzhao on 22/09/2026.
//

#include "format.h"
#include "record.h"
#include "bytes.h"
#include "serialization.h"

#include <fcntl.h>    // open(), O_RDONLY, O_RDWR, O_CREAT...
#include <unistd.h>   // read(), write(), lseek(), close()
#include <sys/types.h>// ssize_t, off_t
#include <sys/stat.h> // permission constants such as 0644
#include <errno.h>    // errno
#include <stdalign.h>
#include <stdio.h>
#include <string.h>


const char *mldb_strerror(MldbStatus s) {

}





MldbStatus  save_library(const char *path, const Library *lib) {
    int fd = open(path, O_RDWR);


    //header
    Header header = (Header){
        .version = MLDB_VERSION,
        .record_count = lib->arena->used,
        .reserved = alignof(__alignof__(lib->arena->used)),
    };
    memcpy(&header.magic, MLDB_MAGIC, sizeof(header.magic));

    //serialize header
    uint8_t headerByte [18];
    put_le(header.magic, headerByte, sizeof(header.magic));
    put_le(header.version, headerByte+4, sizeof(header.version));
    put_le(header.reserved, headerByte+6, sizeof(header.reserved));
    put_le(header.record_count, headerByte+8, sizeof(header.record_count));

    size_t trackCount = lib->count;
    int trackSizeByte = 24;
    //record table
    uint8_t trackListByte [trackSizeByte * trackCount];
    uint8_t trackOffsets [trackCount];
    uint8_t artistOffsets [trackCount];

    uint8_t temp_nextIndex = 0;
    uint32_t strLenTotal = 0 ;
    for (int i = 0; i<trackCount; i++) {
        uint8_t trackByte [trackSizeByte];
        uint8_t titleOffset = temp_nextIndex;
        trackOffsets[i] = titleOffset;
        Track track = lib->tracks[i];
        temp_nextIndex += strlen(track.title);

        uint8_t artistOffset = titleOffset + temp_nextIndex;
        artistOffsets[i] = artistOffset;
        temp_nextIndex += strlen(track.artist);

        record_pack(&track, titleOffset, artistOffset, trackByte);

        memcpy(trackListByte + i * trackSizeByte, trackByte, trackSizeByte);

        strLenTotal += strlen(track.title) + strlen(track.artist);
    }

    uint8_t stringBytes[strLenTotal];
    memcpy(stringBytes, lib->arena->buffer,  strLenTotal);

    put_le(trackCount, headerByte+12, sizeof(uint16_t));
    put_le(strLenTotal, headerByte+14, sizeof(uint32_t));


    const size_t totalSize = 12 + trackSizeByte * trackCount + strLenTotal;
    uint8_t combinedToSave [totalSize];
    memcpy(combinedToSave, headerByte, 12);
    memcpy(combinedToSave + 12, trackListByte, trackSizeByte * trackCount);
    memcpy(combinedToSave + trackSizeByte * trackCount, stringBytes, strlenTotal);
    write(fd, combinedToSave, totalSize);
    //string pool
}

MldbStatus  load_library(const char *path, Library *lib) {
    int fd = open(path, O_RDONLY);

    FILE *f = fopen(path, "rb");
    if (!f) return MLDB_E_IO;

    // 1. Seek to the very end of the file
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return MLDB_E_IO;
    }

    // 2. Read the total byte count
    long file_size = ftell(f);
    if (file_size < 20) { // Section 5.5: must be at least 20 bytes for Header
        fclose(f);
        return MLDB_E_TRUNCATED;
    }

    // 3. Rewind to byte 0 so you can begin reading the header
    rewind(f);

    uint8_t buffer [file_size];

    read(fd, buffer, file_size);

    library_create(lib, TRACK_FIELDS_COUNT);

    //handle whether size of titles list are static set on the #TRACK_FIELDS_COUNT

    uint8_t *start = buffer + 20;

    uint8_t  *titles_offset [TRACK_FIELDS_COUNT];
    uint8_t *artists_offset [TRACK_FIELDS_COUNT];

    uint64_t totalTitleArtistLength = 0;
    for (int i = 0; i<TRACK_FIELDS_COUNT; i++) {
        Track track;

        uint16_t title_len;
        memcpy(&title_len, start+12, sizeof(title_len));
        totalTitleArtistLength += title_len;
        titles_offset[i] = start+12;

        uint32_t title_offset;
        memcpy(&title_offset, start+14, sizeof(title_offset));


        uint16_t artist_len;
        memcpy(&artist_len, start+18, sizeof(artist_len));
        totalTitleArtistLength += artist_len;
        artists_offset[i] = start+18;

        uint32_t artist_offset;
        memcpy(&artist_offset, start+20, sizeof(artist_offset));

        record_unpack(start, &track, &title_len, &title_offset, &artist_len, &artist_offset);

        library_add(lib, &track);
        start += 24;
    }

    Arena *arena = arena_create(TRACK_FIELDS_COUNT * sizeof(Track*) + totalTitleArtistLength);
    for (int i = 0; i<TRACK_FIELDS_COUNT-1; i++) {
        uint16_t titleLength = artists_offset[i] - titles_offset[i];
        uint16_t artistLength = titles_offset[i+1] - artists_offset[i];
        void *strPtr = arena_calloc(arena, 1, titleLength + artistLength);
        memcpy(strPtr, titles_offset[i], titleLength);
        memcpy(strPtr + titleLength, artists_offset[i], artistLength);
    }

    //last
    uint16_t titleLength = artists_offset[TRACK_FIELDS_COUNT -2] - titles_offset[TRACK_FIELDS_COUNT -2];
    uint16_t artistLength = &buffer[file_size-1] - artists_offset[TRACK_FIELDS_COUNT -2];
    arena_calloc(arena, 1, titleLength + artistLength);
    void *strPtr = arena_calloc(arena, 1, titleLength + artistLength);
    memcpy(strPtr, titles_offset[TRACK_FIELDS_COUNT -2], titleLength);
    memcpy(strPtr + titleLength, artists_offset[TRACK_FIELDS_COUNT -2], artistLength);
    
}