//
// Created by cleme on 24/08/2026.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
const char *msg = "hello";
#include "helper.h"

int global = 42;

void foo() {
    int local = 20;
    int *p = malloc(4);
    printf("Local: %p\n", &local);
    printf("Address Allocated by Malloc: %p\n", p);
    printf("Address that store the address: %p\n", &p);
    printf("Size of malloc(4): %llu bytes\n", sizeof(p));
    free(p);
}
struct Point {
    char x;//1
    int y; //4
    double z; //8
};

union Data {
    // struct Point point[2];
    // double e;
    // char test[10];
    struct Point p;
};

union float_address {
    float number;
    unsigned char address;
};


/*
 *
 *
 */

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
    bool initialized;
} IntArray;

void arr_push(IntArray *a, int val) {
    if (!a->initialized) {
        printf("ERROR: Pushing into an uninitialized Array!");
        return;
    }
    size_t size = a->size;

    if (size >= a->capacity) {
        a->data = realloc(a, ++size);
        a->data[size-1] = val;
    }
}

void arr_pop(IntArray *a) {
    if (!a->initialized) {
        printf("ERROR: Popping from an uninitialized Array!");
        return;
    }
    int* temp_ptr = a->data;
    if (a->size > 0) {
        while (temp_ptr != &a->data[a->size-1]) {
            temp_ptr++;
        }
        free(temp_ptr);
    }
}


void initialize_arr(IntArray *a, int size) {
    *a = (IntArray){
        .data = calloc(size, sizeof(int)),
        .size = size,
        .capacity = size,
        .initialized = true
    };
}

void expanding_array() {
    typedef struct {
        int *data;
        size_t size;
        size_t capacity;
    }dynamicArray;

    // int userInput;
    // char buffer[100];
    // char *end_ptr;
    // while (userInput != -1) {
    //     printf("");
    //     // scanf("Enter Number to Insert (-1 to exit): %d", &userInput);
    //     bool validInput = true;
    //     while (!validInput) {
    //         strtol(buffer, &end_ptr, 10);
    //         if (end_ptr == buffer) {
    //             validInput = false;
    //             printf("Input is Empty!");
    //         }
    //         if (errno == ERANGE) {
    //             printf("Number Out of Range");
    //         }
    //         if (fgets(buffer, 10, stdin) == NULL) {
    //
    //         }
    //     }
    //
    // }


}

union float_address float_addresses (float* floaty) {
    union float_address floatItem;
    unsigned char *ptr = (unsigned char*)&floatItem;
    floatItem.number = *floaty;
    for (int i =0; i<sizeof(*floaty); i++) {
        floatItem.address = ptr[i];
        printf("Address of floatItem: %p\n", &floatItem);
    }
}

int pointerSearch(int arr[], int findIndexOf) {
    //instead for loop
    int* start = arr;
    int* ptr = arr;
    while (*ptr != findIndexOf) {
        ptr++;
    }
    return (int)(ptr-start);
}

int my_strlen(char *s) {
    int x = 0;
    while (s[x] != '\0') {
        x++;
    }
    return x;
}
void my_strcopy(char* dest, char *str, int mallocSize) {
    int strLen = my_strlen(str);
    if (mallocSize > strLen) {
        return;
    }
    const char *str_ptr = strdup(str);

    while (*str_ptr != '\0') {
        dest = str;
        dest++;
        str_ptr++;
    }
    //without he pointer its just this for loop no?
    // for (int i = 0; i<strLen; i++) {
    //     dest[i] = str_ptr[i];
    // }
}

void void_size(void *something) {
    //method 1:
    char s = *(char*)something;
    //method 2:
    char *loc = something;
    char another_s = *loc;
}

void *my_memcpy(void *dest, const void *src, size_t n) {

    char* c_src = (char*) src;
    char* c_dest = dest;

    for (int i = 0; i < n; i++) {
        c_dest[i] = c_src[i];
    }
    return dest;
}

void two() {
    int arr[5] = {10, 20, 30, 40, 50};
    printf("Size of arr byte: %llu\n", sizeof(arr));
    int *p = arr;

    int *q = &arr[4];
    ptrdiff_t diff = q - p;  // 4, not 16

    printf("q-p =  %lld \n", diff);

    printf("address of arr: %p\n", &arr);
    printf("address of p: %p\n", *p);
}
// void print(void *ptr) {
//     switch (sizeof(*ptr)) {
//         case 1:
//             print()
//     }
// }
int main(int argc, char *argv[]) {
    /*foo();
    two();
    printf("Global Address: %p\n", &global);
    printf("sizeof(double *): %llu bytes\n", sizeof(double *));

    char* string = "theres no string in C";
    printf("Size of string: %llu bytes\n", sizeof(*string));*/

    union Data data;
    struct Point p;
    printf("Size of Data: %llu\n", sizeof(data));
    printf("Size of Point: %llu\n", sizeof(p));

}
