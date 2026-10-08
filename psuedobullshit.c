//
// Created by clementzhao on 17/09/2026.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int factorial (const unsigned int input) {
    int fact = input;
    int dup = input-1;

    while (dup > 0) {
        printf("%d *", dup);
        fact *= dup--;
    }
    return fact;
}

bool isLeap(const unsigned int year) {
    return year % 4 ==0 && year % 100 ==0 && year % 400 == 0;
}

int main(int argc, char *argv[]) {
    /*char *end_ptr;
    char buffer [100];
    scanf("Enter a number to be factorialized: %s", buffer);
    unsigned int input =  strtol(buffer, &end_ptr, 10);


    int output = factorial(input);
    printf("%d\n", output);

    scanf("Enter a year: %d", &input);
    bool leap = isLeap(2020);
    printf("%s", leap ? "leap" : "not leap");
    */


    int inputMenu = 0;
    char **calcHistory;
    while (inputMenu != 4) {
        printf("==CALCULATION PROGRAM=="
               "\nChoose Your Action: "
               "\n(1)Addition"
               "\n(2)Substraction"
               "\n(3)View calculation history"
               "\n(4)Exit");
        scanf("Input: %d", &inputMenu);

        switch (inputMenu) {
            case 1:
                int a, b;
                scanf("%d + %d", &a, &b);
                printf("Result: %d", a+b);
                break;
            case 2:
                int c, d;
                scanf("%d - %d", &c, &d);
                printf("ResultL %d", a-b);
            case 3:

        }

    }

}
