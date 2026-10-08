//
// Created by clementzhao on 06/09/2026.
//

/*
 * SERIES OF ADVANCED C Programming by Charles Cabergs:
 * https://www.youtube.com/playlist?list=PL71Y0EmrppR0KyZvQWj63040UEzKQU7n8
 *
 * File will be a compilation of trial and error, utilizing and follwing per each vid of the series.
 */

//EP 2: Bit Pointers

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>

// #define FLAG_ACK        (1U << 7)
// #define FLAG_NACK       (1U << 6)
// #define FLAG_RETRY      (1U << 5)
// #define FLAG_COMPRESSED (1U << 4)
// #define FLAG_ENCRYPTED  (1U << 3)
// #define FLAG_PRIORITY   (1U << 2)
// #define FLAG_RESERVED1  (1U << 1)
// #define FLAG_RESERVED2  (1U << 0)



typedef enum {
    FLAG_RESERVED2 = 1U << 0,
    FLAG_RESERVED1 = 1U << 1,
    FLAG_PRIORITY = 1U << 2,
    FLAG_ENCRYPTED = 1U << 3,
    FLAG_COMPRESSED = 1U << 4,
    FLAG_RETRY = 1U << 5,
    FLAG_NACK = 1U << 6,
    FLAG_ACK = 1U << 7
}e_flag;

typedef struct {
    char* name;
    e_flag ptr;
}Flag;

void inputInt(uint32_t *assignTo, int bufferSize) {
    char buffer[bufferSize];
    if (fgets(buffer, bufferSize, stdin) != NULL) {
        errno =0;
        char * endPtr;
        long val = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && *endPtr == '\0' || *endPtr == '\n') {
            *assignTo = (int)val;
        }
    }
}

typedef union {
    uint32_t num;
    bool flags [8];
}Value;


typedef struct{
    char*name;
    int size;
    int start_index;
    int end_index;
    Value value;
}Specification;

void printSpec(Specification specs[], int specAmount) {
    for (int i = 0; i<specAmount; i++) {
        printf("%s SPECS: size: %d, start_index: %d, end_index: %d, num: %d\n", specs[i].name, specs[i].size, specs[i].start_index, specs[i].end_index, specs[i].value.num);
    }
}

void setupSpecDetails(int specAmount, Specification specs[], const int sizes[],  char* names[]) {
    int currentPos = 0;
    for (int i =0; i< specAmount ;i++) {
        specs[i] = (Specification){
            .name = names[i],
            .size = sizes[i],
            .start_index = currentPos,
            .end_index = currentPos + sizes[i]-1,
        };
        currentPos = currentPos + sizes[i];
    }
    printSpec(specs, specAmount);
}

void setNum(uint32_t input, Specification* spec) {
    const uint32_t shifted = input >> (32-(spec->end_index+1) );
    printf("debug %d\n", 32-(spec->end_index+1));
    printf("shifted: %d\n", shifted);
    const uint32_t maskLeft = (1U << spec->size) - 1U;

    const uint32_t num = shifted & maskLeft;
    spec->value.num = num;
}

void decrypt(uint32_t input, int len, char* names[], const int sizes[], char* flags []) {
    const int specAmount = 5;

    Specification specs[specAmount];
    setupSpecDetails(specAmount, specs, sizes, names);
    printf("SPECIFICATIONS: ");
    for (int i =0; i < specAmount-1; i++) {
        setNum(input, &specs[i]);
        printf( "%s: %d\n", specs[i].name, specs[i].value.num);
    }

    const int flagsCount = 8;

    printf("FLAGS: \n");
    for (int i = 0; i < sizes[specAmount-1]; i++) {
        const bool state = (input >> (flagsCount - i - 1)) & 1U;
        specs[specAmount-1].value.flags[i- (len - sizes[specAmount-1])] = state;
        printf("%s: %s\n", flags[i], state ? "true" : "false" );
    }
}

static char* substring (char *str,  int start, int end) {
    char* outputStr = calloc(end-start+1, sizeof(char));

    char* startPtr = str+start;

    for (int i = 0; i <= end-start; i++) {
        *(outputStr+i) = *(startPtr+i);
    }

    *(outputStr+(start-end)) = '\0';
    return outputStr;
}

uint32_t pow(int base, int exp) {
    for (int i =0; i<exp; i++) {
        base *= base;
    }
    return base;
}
static size_t sizeOfArr(void** array) {
    size_t size = 0;
    while (array[size] != NULL) {
        size++;
    }
    return size;
}


void encrypt( Flag flags[], const int sizes[], char* names[]) {
    printf("ENCRYPTION PROTOCOL");
    printf("\nEnter these Inputs: ");
    for (int i =0; i < len; i++) {

    }


    int booleans = 0U;

    for (int i =0; i<sizeOfArr(flags[i])-1; i++) {
        int input;
        printf("Input %s's Number 0-%d",  flags[i].name ,pow(2, sizes[i])-1);
        scanf("%d", &input);
        if (input) {
            booleans |= flags[i].ptr;
        }
    }

}





const void**  heaps [1024];
// typedef struct List List;




int main(int argc, char *argv[]) {
    // uint32_t input;
    // printf("Enter an integer: ");
    // const int len = 32;
    // inputInt(&input, len);
    // char* names [] = {"device_id", "op_code", "payload_length", "checksum", "flags"};
    // const int sizes [] = {3,2,10,9,8};
    // const uint32_t ALL_FLAGS[] = {
    //     FLAG_ACK,
    //     FLAG_NACK,
    //     FLAG_RETRY,
    //     FLAG_COMPRESSED,
    //     FLAG_ENCRYPTED,
    //     FLAG_PRIORITY,
    //     FLAG_RESERVED1,
    //     FLAG_RESERVED2
    // };
    // char* flags[] = {"FLAG_ACK", "FLAG_NACK", "FLAG_RETRY", "FLAG_COMPRESSED", "FLAG_ENCRYPTED", "FLAG_PRIORITY", "FLAG_RESERVED1", "FLAG_RESERVED2"};
    //
    // decrypt(input, len, names, sizes, ALL_FLAGS, flags);

    Flag flags[] = {
        {
            .name ="FLAG_ACK",
            .ptr = FLAG_ACK
        },
        {
            .name ="FLAG_NACK",
            .ptr = FLAG_NACK
        }
    };

    sizeOfArr(flags);
    char* str = calloc(128, sizeof(char));
    scanf("%s", str);
    char* sub = substring(str, 4, 10);
    printf("substring: %s\n", sub);
    free(str);



}












