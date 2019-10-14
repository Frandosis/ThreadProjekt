#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "functions.h"
#include "dynamicarray.h"


int main() {
    Array arr1;
    Array arr2;

    initArray(&arr1, 2, 100);
    initArray(&arr2, 2, 100);

    towerOfHanoi(&arr1, 3, 'A', 'C', 'B');

    for (size_t i = 0; i < arr1.used; i++){
        printf("Arr[%d]: %s", i, arr1.array[i]);
    }
    printf("Size of Array: %ld\n", arr1.size);

    freeArray(&arr1);
    int i = fibonacci(&arr2, 0, 1, 10000);
    for (size_t i = 0; i < arr2.used; i++){
        printf("Arr[%d]: %s", i, arr2.array[i]);
    }
    printf("Size of Array: %ld\n", arr2.size);
    printf("Number of iterations: %d\n", i);
    freeArray(&arr2);
    return 0;
}