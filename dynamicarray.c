//
// Created by s184805 on 14-10-2019.
//
#include <stdlib.h>
#include <string.h>
#include "dynamicarray.h"


void initArray(Array *a, size_t initialSize, size_t stringsize) {
    char * e = "test";
    a->array = (char **)calloc(initialSize, sizeof(&e));
    a->used = 0;
    a->size = initialSize;
    a->strsize = stringsize;
}
void addString(Array *a, char *element) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (a->used == a->size) {
        char * e = "test";
        a->size *= 2;
        a->array = (char **)realloc(a->array, a->size * sizeof(&e));
    }
    a->array[a->used++] = element;
}
int contains(Array* a, char * element)
{
    for (size_t i = 0; i < a->used; i++){
         if(strcmp(element, a->array[i]) == 0){
            return 1;
         }
     }
     return 0;
}
void freeArray(Array *a) {
    //first free every string in the array.
    for (size_t i = 0; i < a->size; i++){
        char * str = *(a->array+i);
        free(str);
    }
    //then free the array of strings.
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

