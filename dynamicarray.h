//
// Created by s184805 on 14-10-2019.
//

#ifndef THREADPROJEKT_DYNAMICARRAY_H
#define THREADPROJEKT_DYNAMICARRAY_H
typedef struct {
    char **array;
    unsigned long int used;
    unsigned long int size;
    unsigned long int strsize;
} Array;


void initArray(Array *a, unsigned long int initialSize, unsigned long int stringsize);
void addString(Array *a, char *element);
int contains(Array* a, char * element);
void freeArray(Array *a);

#endif //THREADPROJEKT_DYNAMICARRAY_H
