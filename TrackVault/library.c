//
// Created by clementzhao on 21/09/2026.
//

#include <stdlib.h>
#include "library.h"

#include <string.h>

#include "arena.h"
#include "index.c"
#include "format.h"


//
// MldbStatus library_create(Library *lib, size_t arena_capacity);
// MldbStatus library_add(Library *lib, const Track *t);   /* copies strings into arena */
// void       library_free(Library *lib);



MldbStatus library_create(Library *lib, size_t arena_capacity) {
    lib->arena = arena_create(arena_capacity);
    lib->tracks = calloc(1<<8, sizeof(Track));
    lib->count = 0;
    index_init(arena_capacity, &lib->index);
}

MldbStatus library_add(Library *lib, const Track *t) {
    if (sizeof(Track)  * (lib->count + 1) >= ARENA_TRACK_CAPACITY) {
        return MLDB_E_NOMEM;
    }
    lib->tracks = arena_calloc(lib->arena, 1,  sizeof(Track));
    lib->count++;

    // uint8_t *buffer=  lib->arena->buffer + lib->arena->used;
    // Track *track = &lib->tracks[lib->count-1];
    // *buffer = t->title;
    // buffer+= sizeof(t->artist);
    // *buffer = t->artist;
    Arena *trackSpaceSize = lib->arena + (ARENA_TRACK_CAPACITY) * sizeof(Track);

    size_t offsetTitlePreTracks = lib->count * (sizeof(t->title) + sizeof(t->artist));

    void* title_loc = arena_calloc( trackSpaceSize + offsetTitlePreTracks, 1, sizeof(t->title));
    //copy per bit char of hte string. the memset just replaces whole stuff with hte int inserted
    memcpy(t->title, title_loc, strlen(t->title)+1);

    //give space
    void *artist_loc = arena_calloc(trackSpaceSize + offsetTitlePreTracks + sizeof(t->title), 1, sizeof(t->artist));
    memcpy(t->artist, artist_loc, strlen(t->artist)+1);


}   /* copies strings into arena */

MldbStatus library_free(Library *lib) {
    free(lib->tracks);
    arena_destroy(lib->arena);
    index_destroy(&lib->index);
    free(lib);
}

