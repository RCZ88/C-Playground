#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Created by clementzhao on 14/09/2026.
//

// const int START = 0;
// const int END = 1;
// typedef struct {
//     char* str;
//     size_t len;
//     char* temp_ptr;
//     char* edge_address [2];
//     int expandRate;
// }String;
//
// String newString(char* str, int expandRate) {
//     size_t len = strlen(str);
//     int expandCount = len/expandRate + 1;
//
//     char* edge_address [2]= {
//         ,
//
//     };
//     return String{
//
//     }
// }


static int sum(int count, ...) {
    va_list ap;
    va_start(ap, count);

    int sum = 0;
    for (int i = 0; i<count; i++) {
        sum += va_arg(ap, int);
    }
    va_end(ap);
    return sum;
}

const char* FILENAME = __FILE__;


typedef struct {
    void* heap;
    size_t size;
    const char* filename;
    int line;
    int index;
    bool freed;
}HeapMD;

static HeapMD *heaps;
static int count =0;
static uint32_t cap;


static void handleFull() {
    if (count >= cap) {
        heaps = realloc(heaps, cap*2);
        cap *= 2;
    }
}


static void initHeaps(const uint32_t capacity) {
    heaps = (HeapMD*)calloc(capacity, sizeof(HeapMD));
    cap = capacity * sizeof(HeapMD);
}


static HeapMD callocc(const uint32_t amount, const size_t size, const int line) {
    void *ptr = calloc(amount, size);
    const size_t total = size * amount;
    handleFull();
    heaps[count] = (HeapMD){
        .heap = ptr,
        .size = total,
        .filename = FILENAME,
        .line = line,
        .index = count,
        .freed = false
    };
    count++;
    return heaps[count-1];
}

static HeapMD reallocc(void* ptr, const size_t size, const int line) {
    void* new_ptr = realloc(ptr, size);
    handleFull();
    heaps[count] = (HeapMD){
        .heap = new_ptr,
        .size = size,
        .filename = FILENAME,
        .line = line,
        .index = count,
        // .freed = false
    };
    count++;
    return heaps[count-1];
}

static bool linSearch(void *key, void *foundArr[], int foundCount) {
    for (int i = 0; i < foundCount; i++) {
        if (foundArr[i] == key) {
            return true;
        }
    }
    return false;
}

static void freee() {
    void *foundArr[count];
    int foundCount = 0;

    for (int i = 0; i < count; i++) {
        if (!linSearch(heaps[i].heap, foundArr, foundCount)) {
            foundArr[foundCount++] = heaps[i].heap;
            free(heaps[i].heap);
        }
    }

    free(heaps);
}

static void freeOne(const int line) {
    for (int i = 0; i<count; i++) {
        if (heaps[i].line == line) {
            free(heaps[i].heap);
            heaps[i].freed = true;
            break;
        }
    }
}

static void substring (char *str, const int start, const int end, char **returnStr) {
    char* outputStr = callocc(end-start+1, sizeof(char), __LINE__).heap;

    char* startPtr = str+start;

    for (int i = 0; i <= end-start; i++) {
        *(outputStr+i) = *(startPtr+i);
    }

    *(outputStr+(start-end)) = '\0';

    *returnStr = outputStr;
}


static void reverse(char *str, int size, char** result) {
    char *strPtr = reallocc(str, size, __LINE__).heap;
    char *rev = callocc(size+1, sizeof(char), __LINE__).heap;
    printf("reversed:");
    for (int i = size - 1; i >= 0; i--) {
        rev[size-i-1] = strPtr[i];
        printf("%c", strPtr[i]);
    }
    printf("\n");

    rev[size] = '\0';

    *result = rev;
}

static unsigned int length(const char* str) {
    unsigned int c = 0;
    const char* dup = str;
    while (*dup != '\0') {
        dup++;
        c++;
    }
    return c;
}

void concat(const char *str1, const char *str2, char** returnString) {
    const unsigned int lenTotal = length(str1) + length(str2);
    char string [lenTotal+1];
    for (int i = 0; i<lenTotal; i++) {
        if (i < length(str1)) {
            string[i] = *str1++;
            continue;
        }
        string[i] = *str2++;
    }
    string[lenTotal] = '\0';
    *returnString = string;
}

typedef struct {
    char* string;
    int len;
}BinaryData;

// char* printBinaryData(BinaryData data) {
//     return concat();
// }


static int binaryToDenary(const char *binary) {
    int num = 0;

    while (*binary != '\0') {
        num = num * 2  +  (int)*binary++;
    }
    return num;
}


static void denaryToBinary(int integer, BinaryData *result) {
    HeapMD ibt_HMD = callocc(100, sizeof(char), __LINE__);
    char* int_bin_temp = ibt_HMD.heap;
    int size_int = 0;
    printf("pre reversal binary: ");
    while (integer != 0) {
        int_bin_temp[size_int++] = (char)(integer % 2 + '0');
        integer = integer / 2;
        printf("%c", int_bin_temp[size_int-1]);
    }
    printf("\n");

    char *int_bin = callocc(size_int, sizeof(char), __LINE__).heap;
    reverse(int_bin_temp, size_int, &int_bin);
    printf("post reversal variable input param, outputs: %s\n", int_bin);

    *result = (BinaryData){
        .len = size_int,
        .string = int_bin
    };
}

static void decimalNumberToBinary(int decimalNumber, int lengthDecimal,  BinaryData *result) {
    double denary = decimalNumber / pow(10, lengthDecimal);
    printf("Decimal Binary of %f: ", denary);
    const int required = 23;
    char *heap = callocc(required+1, sizeof(char), __LINE__).heap;
    for (int i = 0; i<required; i++) {
        denary *=2;
        // printf("dVal(%f) = ", denary);
        if (denary > 1.0) {
            heap[i] = '1';
            denary -= 1.0;
            printf("%c", heap[i]);
            continue;
        }
        heap[i] = '0';
        printf("%c", heap[i]);
    }
    heap[required] = '\0';

    printf("\n");

    *result = (BinaryData){
        .len = required,
        .string = heap,
    };
}

static BinaryData concatBinaryComponents(BinaryData sign, BinaryData exponent, BinaryData mantissa) {
    char *binary = callocc(32, sizeof(char), __LINE__).heap;
    // binary[0] = sign.string[0];
    // for (int i = 1; i<32; i++) {
    //     if (i<exponent.len+sign.len) {
    //         binary[i] = exponent.string[i];
    //         continue;
    //     }
    //     binary[i] = mantissa.string[i];
    // }

    binary = strcat(sign.string, exponent.string);
    binary = strcat(binary, mantissa.string);

    return (BinaryData){
        .len = 32,
        .string = binary,
    };
}




int main(int argc, char *argv[]) {
    initHeaps(1<<6);

    const int portion = 20;
    char input [portion];
    scanf("%s", input);
    int decimalIndex = 0;
    int len = 0;
    for (int i = 0; i < portion; i++) {
        if (input[i] ==  '.') {
            decimalIndex = i;
        }
        if (input [i] == '\0') {
            break;
        }
        len++;
    }
    printf("decimalIndex: %d\n", decimalIndex);
    printf("len: %d\n", len);
    //check if negative
    char *negative = input[0] == '-' ? "1" : "0";
    BinaryData sign = (BinaryData){
        .len = 1,
        .string = negative,
    };
    printf("\nSign(l=%d): %s\n\n", sign.len, sign.string);

    char *intString;
    substring(input, 0, decimalIndex-1, &intString);
    char *decimalString;
    substring(input, decimalIndex+1, len-1, &decimalString);

    printf("intString: %s\n", intString);
    printf("decimalString: %s\n", decimalString);
    char *end_ptr;

    int integer = (int) strtol(intString, &end_ptr, 10);
    int decimal = (int) strtol(decimalString, &end_ptr, 10);


    BinaryData rawBin;
    printf("Binary for Length Integer(%s)\n", intString);
    denaryToBinary(integer, &rawBin);
    const int sizeOfInteger = rawBin.len;
    const int exponentInDenary =  sizeOfInteger -1 + 127;
    BinaryData exponent;
    printf("Binary for Exponent Integer(%d)\n", exponentInDenary);
    denaryToBinary(exponentInDenary, &exponent);
    printf("\nExponent(l = %d): %s\n", exponent.len, exponent.string);

    BinaryData mantissa;
    decimalNumberToBinary(decimal, len-decimalIndex-1, &mantissa);
    printf("\nMantissa (l = %d): %s\n", mantissa.len, mantissa.string);
    //
    // BinaryData fin = concatBinaryComponents(sign, exponent, mantissa);
    // printf("%s\n", fin.string);

    printf("%s in IEEE-754 format = %s%s%s..._2 x 2^8", input, sign.string, exponent.string, mantissa.string);

    freee();
    return 0;
}
