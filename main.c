#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "functions.h"
#include "dynamicarray.h"


int main() {
    Array arr1;
    int n = 8;

    initArray(&arr1, 2, 100);

    towerOfHanoi(&arr1, n, 'A', 'C', 'B');

    if(tOHPlayer(&arr1, n) != 1) {
        printf("Something went wrong playing the game");
    } else {
        printf("Tower of Hanoi has been played and solved");
    }

    freeArray(&arr1);

    return 0;
}