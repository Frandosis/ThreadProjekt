#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "functions.h"
#include "dynamicarray.h"
#include <string.h>

#define TOH_DISK 10

FILE * fptr;
sem_t filelock;
int primelock;
int fibonaccilock;
sem_t tohlock;


void * primeWr(void * t){
    printf("Starting thread %ld\n", (long) t);
    long retval = 0;
    char * str;
    Array numbers;
    initArray(&numbers, 2, 15);

    //generate primenumbers from 0 to the maximum number in the rand() function.
    for (int i = 0; i < RAND_MAX; i++){
        if(isPrimeRt(i) == 1) {
            str = (char *) calloc(numbers.strsize, sizeof(char));
            sprintf(str, "%d", i);
            addString(&numbers, str);
        }
    }
    /*
    while(fibonaccilock == 1 || tohlock == 1){

    }*/
    sem_wait(&filelock);

    if((fptr = fopen("file.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = 0;
        pthread_exit((void*)retval);
    }

    for (long i = 0; i < numbers.used; i++){
        fprintf(fptr, "%s\n", numbers.array[i]);
    }


    primelock = 1;
    fclose(fptr);
    sem_post(&filelock);
    freeArray(&numbers);

    retval = 1;
    pthread_exit((void *) retval);
}

void * primeRd(void * t){
    printf("Starting thread %ld\n", (long) t);
    time_t t1;
    long retval = 0;
    Array numbers;
    initArray(&numbers, 2, 15);
    char * str;

    while (primelock != 1){

    }
    sem_wait(&filelock);

    if((fptr = fopen("file.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = 0;
        pthread_exit((void*) retval);

    }
    while (!feof(fptr)){
        str = (char *) calloc(numbers.strsize, sizeof(char));
        fscanf(fptr,"%s",str);
        addString(&numbers, str);
    }


    fclose(fptr);
    primelock = 0;
    sem_post(&filelock);

    long * primes = (long *) calloc(numbers.used, sizeof(long));
    for(size_t i = 0; i < numbers.used; i++){
        char * tmp;
        primes[i] = strtol(numbers.array[i], &tmp, 10);
    }
    long psize = numbers.used;
    freeArray(&numbers);

    srand((unsigned int) time(&t1));

    retval = 0;
    for(int i = 0; i < 100; i++){
        int random = rand();
        for(long j = 0; j < psize; j++){
            if (random == primes[j]){
                retval++;
            }
        }
    }

    free(primes);
    pthread_exit((void *) retval);
}

void * fibonacciWr(void * t){
    printf("Starting thread %ld\n", (long) t);
    long retval = 0;
    long n = RAND_MAX;

    Array numbers;
    initArray(&numbers, 2, 15);

    fibonacci(&numbers, 0, 1, n);

    /*while(primelock == 1 || tohlock == 1){

    }*/
    sem_wait(&filelock);

    if((fptr = fopen("file.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = 0;
        pthread_exit((void*)retval);
    }

    for (size_t i = 0; i < numbers.used; i++){
        fprintf(fptr, "%s\n", numbers.array[i]);
    }

    fclose(fptr);
    fibonaccilock = 1;
    sem_post(&filelock);
    freeArray(&numbers);
    retval = 1;
    pthread_exit((void *)retval);
}

void * fibonacciRd(void * t){
    printf("Starting thread %ld\n", (long) t);
    long retval = 0;
    time_t time1;
    Array numbers;
    long * fibnum;
    char * str;

    while(fibonaccilock != 1){

    }
    sem_wait(&filelock);

    if((fptr = fopen("/file.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = 0;
        pthread_exit((void*) retval);

    }

    while (!feof(fptr)){
        str = (char *) calloc(numbers.strsize, sizeof(char));
        fscanf(fptr,"%s",str);
        addString(&numbers, str);
    }

    fclose(fptr);
    fibonaccilock = 0;
    sem_post(&filelock);

    fibnum = (long *) calloc(numbers.used, sizeof(long));
    for(long i = 0; i < numbers.used; i++){
        char * tmp;
        fibnum[i] = strtol(numbers.array[i], &tmp, 10);
    }

    long fnsize = numbers.used;
    freeArray(&numbers);

    srand((unsigned int) time(&time1));

    retval = 0;
    for(int i = 0; i < 100; i++){
        int random = rand();
        for(long j = 0; j < fnsize; j++){
            if (random == fibnum[j]){
                retval++;
            }
        }
    }
    free(fibnum);
    pthread_exit((void *) retval);

}

void * towerOfHanoiWr(void * t){
    sem_wait(&tohlock);
    printf("Starting thread %ld\n", (long) t);
    size_t strsize = 100;
    Array ins;
    long retval = 0;
    int n = TOH_DISK;
    char * filename = (char *) calloc(strsize, sizeof(char));

    filename = getcwd(filename, strsize);
    strcat(filename, "\\file.txt");

    initArray(&ins, 2, strsize);

    towerOfHanoi(&ins, n, 'A', 'C', 'B');

    while(primelock == 1 || fibonaccilock == 1){

    }
    sem_wait(&filelock);

    if((fptr = fopen(filename, "w")) == NULL) {
        puts("File couldn't be opened");
        retval = 0;
        pthread_exit((void*)retval);
    }
    puts("Writing to the file\n");
    for (size_t i = 0; i < ins.used; i++){
        fprintf(fptr, "%s\n", ins.array[i]);
    }

    sem_post(&tohlock);
    fclose (fptr);
    sem_post(&filelock);

    freeArray(&ins);
    free(filename);

    retval = 1;
    pthread_exit((void *) retval);
}

void * towerOfHanoiRd(void * t){
    printf("Starting thread %ld\n", (long) t);
    long retval = 0;
    int n = TOH_DISK;
    char * str;
    Array ins;
    initArray(&ins, 2, 100);

    sem_wait(&tohlock);
    sem_wait(&filelock);

    if((fptr = fopen(".\\file.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = 0;
        pthread_exit((void*) retval);

    }

    while (!feof(fptr)){
        str = (char *) calloc(ins.strsize, sizeof(char));
        fgets(str, ins.strsize, fptr);
        addString(&ins, str);
    }

    fclose(fptr);

    sem_post(&tohlock);
    sem_post(&filelock);
    retval = tOHPlayer(&ins, n);
    freeArray(&ins);
    pthread_exit((void *) retval);
}

int main() {
    int num_t = 2;
    void * (*fun_ptr_arr[])(void *) = {towerOfHanoiWr, towerOfHanoiRd};
    void * retval [num_t];

    pthread_attr_t attr;
    pthread_t threads [num_t];
    long taskids [num_t];
    int rc, t;

    sem_init(&filelock, NULL, 1);
    sem_init(&tohlock, NULL, 1);

    //Create the joinable attributes for the threads.
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Create the threads
    for(t = 0; t < num_t; t++) {
        taskids[t] = t;
        rc = pthread_create(&threads[t], &attr, fun_ptr_arr[t], (void *) taskids[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    //Free attribute and wait for the other threads
    pthread_attr_destroy(&attr);

    for (t = 0; t < num_t; t++){
        rc = pthread_join(threads [t], &retval[t]);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Value returned from thread %d: %ld\n", t, (long) retval[t]);
    }

    sem_destroy(&filelock);

    pthread_exit(NULL);

}