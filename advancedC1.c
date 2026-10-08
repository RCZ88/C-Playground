//
// Created by cleme on 26/08/2026.
//

/*
 * SERIES OF ADVANCED C Programming by Charles Cabergs:
 * https://www.youtube.com/playlist?list=PL71Y0EmrppR0KyZvQWj63040UEzKQU7n8
 *
 * File will be a compilation of trial and error, utilizing and follwing per each vid of the series.
 */



#include <math.h>

#include "helper.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//EP 1:  Function Pointers

//method compiled into memory address
int add(int a, int b) {
    return a+b;
}

bool even(int x) {
    return x%2==0;
}

void print_if(int x, int xs[x], bool (*predicate)(int)) {
    // for (int i = 0; i<x; i++) {
    for (int i = 0; i<x; i++) {
        if (predicate(xs[i])) {
            printf("%d ", xs[i]);
        }
    }
}

typedef const void* AnyConst;

int compare(AnyConst a, AnyConst b) {
    return *(int*)a - *(int*)b;
}

typedef struct {
    char* name;
    int scores[3];

}Student;

int getTotalScore(Student* s) {
    int total = 0;
    for (int i = 0; i<3; i++) {
        total += s->scores[i];
    }
    return total;
}



int compareStudents(AnyConst a, AnyConst b) {
    Student* sa = (Student*)a;
    Student* sb = (Student*)b;

    return getTotalScore(sa) - getTotalScore(sb);
}

int main() {
    int (*f)(int, int) = add;
    int arr[] = {2, 43, 3, 10, 84, 23};
    Student students[] = {
        {.name = "David", .scores = {2,3,4}},
        {.name = "Darrel", .scores = {5,2,3}},
        {.name = "Dicks", .scores = {6,6,3}},
    };
    int length= sizeof(students)/sizeof(students[0]);

    qsort(students, length, sizeof(students[0]), compareStudents);

    for (int i =0; i<length; i++) {
        printf("%s %d\n", students[i].name, students[i].scores[0]);
    }
    print_memory_range(f, sizeof(f));



}

