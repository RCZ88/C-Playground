#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//
// Created by clementzhao on 08/09/2026.
//
typedef struct {
    void* data;
    int size;
}List;

void initList(List *list) {
    list->data = calloc(0, sizeof(void*));
    list->size = 0;
}
void add(List *list, void* data) {
    // if (list->curIndex > list->data) {
    //  dont need if, when the add is only always jut enough.
    // }
    void*temp = realloc(list->data, list->size+1);
    list->data = temp;
    free(temp);
    list->size++;
}
void get(List *list, uint8_t index, void* data) {
    if (index > list->size-1) {
        return;
    }
    *(void**)data = ((void**)list->data)[index];
}

void removeIndex(List *list, uint8_t index) {
    if (index > list->size-1) {
        return;
    }
    if (index != list->size-1) {
        for (int i = index+1; i < list->size; i++) {
            ((void**)list->data)[i-1] = ((void**)list->data)[i];
        }
    }
    void* temp  = realloc(list->data, list->size-1);
    list->data = temp;
    free(temp);
    list->size--;
}




int main(int argc, char *argv[]) {
}
