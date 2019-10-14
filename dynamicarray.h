//
// Created by s184805 on 14-10-2019.
//

#ifndef THREADPROJEKT_DYNAMICARRAY_H
#define THREADPROJEKT_DYNAMICARRAY_H
typedef struct {
    char **array;
    size_t used;
    size_t size;
    size_t strsize;
} Array;

void initArray(Array *a, size_t initialSize, size_t stringsize);
void addString(Array *a, char *element);
void freeArray(Array *a);

#endif //THREADPROJEKT_DYNAMICARRAY_H
