//
// Created by cleme on 19/08/2026.
//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "helper.h"


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int length) {

    for (int i = 0; i<length-1; i++) {
        for (int j =0; j<length-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}



int empty_index(void* array[], int length) {
 for (int i = 0; i<length; i++) {
     if (array[i] == NULL) {
         return i;
     }
 }
    return -1;
}

int main(int argc, char *argv[]) {
    printf("size of int: %llu\n", sizeof(int));
    int iter =0;
    // printf("Input Number of trials: ");
    // scanf("%d", &iter);
    int size = 1000;
    char test[size];

    printf("INPUT WORD: ");
    scanf("%99s", test);
    int count=0;
    while (test[count] != '\0' && count != sizeof(test)) {
        count++;
    }

    // char test2;
    // scanf("%s", &test2);
    // print_memory_range(test2, sizeof(test2));
    char* text = "text";
    print_memory_range(text, strlen(text));

    printf("Text inputted: %s\n", &test);

    print_memory_range(&test, count +1);

    float sizeOfFilledArr = 0;
    if (count >0) {
        sizeOfFilledArr = sizeof(test[0]) * count;
    }
    printf("Size of Filled Array(%d item(s)) in Bits: %f\n", count, sizeOfFilledArr);


    int arr [] = {1,4,2,6,8,3,6,2,9,3,1};
    int length = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, length);
    for (int i =0; i<length; i++) {
        printf("%d", arr[i]);
    }
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error Accepting Input!");
    }

    char *endptr;

    errno = 0;

    long value = strtol(buffer, &endptr, 10);
    //location of endptr because it wants to assign the mem address of the char that cant pass the convertion to long (base 10)

    if (endptr == buffer) {
        printf("No Numbers were inputted");
    }else if (errno == ERANGE) {
        // strtol set the errno to ERANGE when the number is out of range
        printf("Number out of range");
    }else if (*endptr != '\n' && *endptr != '\0') {
        printf("Error: Input contains trailing non-numeric garbage: \"%s\"", endptr);
    } else {
        printf("Successfully parsed integer: %ld\n", value);
    }



    printf("\n");
    printf("%d", 7/2);


    // int x = 10;
    // int y = 20;
    // y = x;
    // // int *ptrX = &x;
    // // *ptrX = y;
    // int input;
    // scanf("Input Integer: %d", &input);
    //
    // struct nums {
    //     float number;
    //     char test [];
    // };
    //
    // // switch (input) {
    // //     case 1:
    // //     case 2:
    // //         print
    // // }
    //
    // int *potato = &x;
    // printf("#%p",  &potato);


}
int fibonacci(int n) {
    int temp = 0;
    int number = 0;
    for (int i = 0; i < n; i++) {
        number = 2*temp+1;
        temp = number;
    }
    printf("%dth Fibonacci Number: %d\n", n, temp);
    return number;
}
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_CHAR
} DataType;

bool valid_input(const char* input, DataType type, void *out_val) {
    switch(type) {
        case TYPE_CHAR:
            if (input[0] == '\n' || input[0] == '\0') {
                return false;
            }
            return true;
        case TYPE_INT:
            if (fgets(input, 10, stdin) == NULL) {




            }
        case TYPE_DOUBLE:

        default:
            return false;
    }
}