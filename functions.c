#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "dynamicarray.h"



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

int fibonacci(Array *a,int prNo, int num, int max)
{
    int nxtNo;
    char c = ' ';
    char * str;

    if (num > max){
        return 0;
    } else {
       nxtNo = prNo + num;
       str = (char *) malloc(a->strsize*sizeof(&c));
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

