#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "dynamicarray.h"
#include "stackandqueue.h"


int bisearch(int * arr, int element, int max){
    int lowerBound = 0;
    int upperBound = max -1;
    int midPoint = -1;
    int index = -1;

    while(lowerBound <= upperBound) {

        midPoint = lowerBound + (upperBound - lowerBound) / 2;

        if(arr[midPoint] == element){
            index = midPoint;
            break;
        } else {
            // if data is larger
            if(arr[midPoint] < element) {
                // data is in upper half
                lowerBound = midPoint + 1;
            }
                // data is smaller
            else {
                // data is in lower half
                upperBound = midPoint -1;
            }
        }
    }
    return index;

}

int tOHPlayer (Array * ins, int n){
    // Initialize the game;
    Stack A, B, C;
    stackInit(&A, n);
    stackInit(&B, n);
    stackInit(&C, n);

    //Load the disk in the stack of rod A.
    for(int j = n; j > 0; j--){
        sPush(&A, j);
    }

    // Run the instructions
    for (size_t i = 0; i < ins->used; i++){
        char * str = ins->array[i];
        char * ptr;
        int x = strtol(str+10, &ptr, 10);

        char c1 = *(ptr+10);
        char c2 = *(ptr+19);

        //First pop the disk from the rod.
        if (c1 == 'A') {
            if (x != sPeek(&A)){
                return 0;
            }
            if(sPop(&A) == 0){
                return 0;
            }

        } else if (c1 == 'B') {
            if (x != sPeek(&B)){
                return 0;
            }
            if(sPop(&B) == 0){
                return 0;
            }

        } else if (c1 == 'C') {
            if (x != sPeek(&C)){
                return 0;
            }
            if(sPop(&C) == 0){
                return 0;
            }
        }

        //Put the disk on the given rod:

        if (c2 == 'A') {
            if (sPush(&A, x) == 0) {
                return 0;
            }
        } else if (c2 == 'B') {
            if (sPush(&B, x) == 0) {
                return 0;
            }
        } else if (c2 == 'C') {
            if (sPush(&C, x) == 0) {
                return 0;
            }
        }
    }
    int j = n;
    for (int i = 0; i < C.size; i++){
           if (j != C.stack[i]){
               return 0;
           }
           j--;
    }

    return 1;
}



void towerOfHanoi (Array* a, int n, char from_rod, char to_rod, char aux_rod){
    char c = ' ';
    char * str = NULL;
    if(n < 1){
        printf("Error: number of disk most at least be one\n");
        return;
    }

    if (n == 1){

        str = (char *) malloc(a->strsize*sizeof(&c));
        sprintf(str, "Move disk %d from rod %c to rod %c", n, from_rod, to_rod);
        addString(a, str);
        return;
    }
    towerOfHanoi(a ,n-1, from_rod, aux_rod, to_rod);
    str = (char *) malloc(a->strsize*sizeof(&c));
    sprintf( str,"Move disk %d from rod %c to rod %c", n, from_rod, to_rod);
    addString(a, str);
    towerOfHanoi(a, n-1, aux_rod, to_rod, from_rod);
}

int fibonacci(Array *a,long prNo, long num, long max)
{
    long nxtNo;
    char c = ' ';
    char * str;
    if(prNo == 0){
        str = (char *) calloc(a->strsize, sizeof(&c));
        sprintf(str,"%d", prNo);
        addString(a, str);
    }

    if (num > max){
        return 0;
    } else {
        nxtNo = prNo + num;
        str = (char *) calloc(a->strsize, sizeof(&c));
        sprintf(str,"%d", num);
        addString(a, str);
        return fibonacci(a, num, nxtNo, max) + 1;
    }
}

int isPrimeRt(int n){

    if( n <= 2){
        if(n <= 1){
            return 0;
        }
        return 1;
    }

    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;

}

int isPrime(int  n){

    if( n <= 2){
        if(n <= 1){
            return 0;
        }
        return 1;
    }

    for (int i = 2; i < n; i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;

}

