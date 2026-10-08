//
// Created by clementzhao on 19/09/2026.
//

#ifndef LEARN_ABC_BYTES_H
#define LEARN_ABC_BYTES_H
#include <stdint.h>
typedef enum {
    SIZE_8 = 1,
    SIZE_16 = 2,
    SIZE_32 = 3,
    SIZE_64 = 4,
}IntSize;

typedef union {
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
}IntVal;

typedef struct {
    IntVal val;
    IntSize size;
}DynamicInt;

static void put_le(uint64_t bit, uint8_t out_byte[], size_t byteSize);
static void get_le(uint64_t out_bit, uint8_t byte[], size_t byteSize);

#endif //LEARN_ABC_BYTES_H
