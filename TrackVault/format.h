//
// Created by clementzhao on 22/09/2026.
//

#ifndef LEARN_ABC_FORMAT_H
#define LEARN_ABC_FORMAT_H
#include "library.h"
#define MLDB_MAGIC "MLDB"
#define MLDB_MAGIC_SIZE 4
#define MLDB_VERSION 1

typedef enum {
    MLDB_OK = 0,
    MLDB_E_IO, MLDB_E_MAGIC, MLDB_E_VERSION, MLDB_E_TRUNCATED,
    MLDB_E_LAYOUT, MLDB_E_RANGE, MLDB_E_OFFSET, MLDB_E_DUPLICATE,
    MLDB_E_NOMEM, MLDB_E_NOTFOUND, MLDB_E_USAGE
} MldbStatus;

const char *mldb_strerror(MldbStatus s);
MldbStatus  save_library(const char *path, const Library *lib);
MldbStatus  load_library(const char *path, Library *lib);

#endif //LEARN_ABC_FORMAT_H
