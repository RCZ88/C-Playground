
#include <stddef.h>
#include <sys/mman.h>
#include <sys/mman.h>
#include <stddef.h>   // size_t
#include <stdio.h>    // optional: perror, printf
//
// Created by clementzhao on 11/09/2026.
//

void *os_alloc(size_t size) {
    void *p = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    if (p == MAP_FAILED)
        return NULL;

    return p;
}

int main(int argc, char *argv[]) {
    // int e = 3;
    // int f = 0;
    //
    // f += e = 6;
    // printf("%d", f);
    //
}
