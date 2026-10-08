//
// Created by clementzhao on 23/09/2026.
//

#include <stddef.h>
#include <stdint.h>

int64_t convertFormat(uint64_t input, uint8_t initSize, uint8_t outSize) {
    return input  >> (initSize - outSize);
}


int main(int argc, char *argv[]) {
    uint8_t num8 = 3439;
    int num32 = 398398234;
    int shift = 32-6;

    int base6 = num32 >> shift;
}



