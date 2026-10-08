#include "helper.h" // Connects header prototype to implementation
#include <ctype.h>
#include <stdio.h>

void print_memory_range(const void *start_address, size_t bytes_to_read) {
    const unsigned char *ptr = start_address;

    printf("Memory Address     | Hex Value | Character\n");
    printf("-------------------|-----------|----------\n");

    for (size_t i = 0; i < bytes_to_read; i++) {
        unsigned char current_byte = ptr[i];

        printf("%p | 0x%02X      | %c\n",
               (void *)(ptr + i),
               current_byte,
               isprint(current_byte) ? current_byte : '.');
    }
}