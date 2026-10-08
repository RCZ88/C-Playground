#include <stdio.h>
#include <string.h>

#include "helper.h"
//
// Created by cleme on 22/08/2026.
//
void no_asterisk(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("No Asterisk Method:\n-in function: a: %d b: %d\n",a,b);
    printf("Memory Location: a: %p, b: %p\n",&a,&b);
}
void with_asterisk(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("Asterisk Method:\n-in function: a: %d b: %d\n",a,b);
    printf("Memory Location: a: %p, b: %p\n",a,b);
}
void arrAccept(int* arr,  int rr1[]) {
    printf("arr: %p arr1: %p\n", arr, rr1); //same

}

void voidArr(void *arr ) {


    // int *p = arr;
    // while (p++ != NULL) {
    //
    // }
}

void length(char *str) {
    int i = 0;
    printf("Addresses of the String: '%s'\n", str);
    while (str[i++] != '\0') {
        printf("%p\n", &str[i]);
    }
    printf("Size = %d\n", i);
}

static int *make(void){
    int a[3]={1,2,3};
    return a;
}   /* gcc will SCREAM */
int main(int argc, char *argv[]) {
    // int a = 1;
    // int b = 2;
    // printf("IN MAIN SPECIFICATION: VALUE(LOCATION) a: %d(%p) b: %d(%p)\n",a, &a, b, &b);
    // no_asterisk(a, b);
    // with_asterisk(&a, &b);
    // int* a_ptr = &a;
    // int* b_ptr = &b;
    // int temp = *a_ptr;
    // *a_ptr = *b_ptr;
    // *b_ptr = temp;

    /*GLM EXERCISES */
    int arr[] = {10,20,30,40,50};
    int *p = arr;
    for (int i = 0; i < 5; i++) {
        printf("Array[%d] = %d    (ptr = %p)\n", i, arr[i], p++);
    }
    printf("&arr = %p\n", &arr);

    //can be represented by the int* instead of needing for it to be an array.
    arrAccept(arr, arr);
    char *str = "test";
    length(str);

    char etest[5];
    for (int i = 0; i < 5; i++) {
        etest['e'+&arr[i]- arr] = str[i];
        etest[4L] = 2;
    }
    size_t size = sizeof(short);
    printf("sizeof(short) = %zu\n", size);
}






