//
// Created by clementzhao on 14/09/2026.
//
#include <fcntl.h>    // open(), O_RDONLY, O_RDWR, O_CREAT...
#include <unistd.h>   // read(), write(), lseek(), close()
#include <sys/types.h>// ssize_t, off_t
#include <sys/stat.h> // permission constants such as 0644
#include <errno.h>    // errno
#include <stdint.h>
#include "bytes.h"

/*
typedef struct {
    u_int32_t offset;
    u_int8_t size;
}Map;



typedef enum {
    MAGIC,
    VERSION,
    RESERVED,
    RECORD_COUNT,
    TABLE_OFFSET,
    POOL_OFFSET,
    POOL_SIZE
}HeaderField;

static Map headerBits[] =  {
    [MAGIC] = (Map){.offset = 0, .size = 4},
    [VERSION] = (Map){.offset = 4,.size = 1 },
    [RESERVED] = (Map){.offset = 5,.size = 1},
    [RECORD_COUNT] = (Map){.offset = 6,.size = 2},
    [TABLE_OFFSET] = (Map){.offset = 8,.size = 4},
    [POOL_OFFSET] = (Map){.offset = 12,.size = 4},
    [POOL_SIZE] = (Map){.offset = 16,.size = 4},
};


typedef struct {
    char magic [4];
    int8_t version;
    int8_t reserved;
}Header;
*/


const int BTB = 8;

//le = Little Endian, stores it reversely. reads it in a reverse manner to. think it like date format 2026-08-17 and 17-08-2026  LE n BE

//bit to byte. input di as bit size int, return as uint8 (bytes)
// static void put_le(DynamicInt di, uint8_t arrPointer[]) {
//      //byte to bit
//     for (int i = 0; i < di.size / BTB; i++) {
//         switch (di.size) {
//             case SIZE_16:
//                 arrPointer[i] = (1U << BTB) - 1U & di.val.u16;
//                 di.val.u16 >>= BTB;
//             case SIZE_32:
//                 arrPointer[i] = (1U << BTB) - 1U & di.val.u32;
//                 di.val.u32 >>= BTB;
//             case SIZE_64:
//                 arrPointer[i] = (1U << BTB) - 1U & di.val.u64;
//                 di.val.u64 >>= BTB;
//             default:
//                 ;
//         }
//     }
// }

static void put_le(const uint64_t bit, uint8_t out_byte[], const size_t byteSize) {
    for (int i = 0; i < byteSize; i++) {
        out_byte[i] = (uint8_t) (bit >> (i * 8));
    }
}

static void get_le(uint64_t out_bit, uint8_t byte[], const size_t byteSize) {
    for (int i = byteSize-1; i >= 0; i--) {
        out_bit <<= byte[i];
    }
}

//byte to bit
// static void get_le(uint8_t arrPointer[], const IntSize sizeByte, DynamicInt *ret) {
//     for (int i = sizeByte/BTB - 1; i >= 0; i--) {
//         switch (sizeByte) {
//             case SIZE_16:
//                 ret->val.u16 = 0;
//                 ret->val.u16 <<= arrPointer[i];
//             case SIZE_32:
//                 ret->val.u32 = 0;
//                 ret->val.u32 <<= arrPointer[i];
//             case SIZE_64:
//                 ret->val.u64 = 0;
//                 ret->val.u64 <<= arrPointer[i];
//         }
//     }
// }


