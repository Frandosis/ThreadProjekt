#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "functions.h"
#include "dynamicarray.h"
#include <string.h>

#define TOH_DISK 20
#define PRIMEMAX 10000000

typedef struct {
    long taskid;
    clock_t start;
    clock_t end;
} Thread_data;

FILE * fptr;
sem_t filelock;
sem_t primelock;
sem_t fibonaccilock;
sem_t tohlock;


void * primeWr(void * t){
    sem_wait(&primelock);
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();
    long retval = 0;
    char * str;
    Array numbers;
    initArray(&numbers, 2, 15);

    //generate primenumbers from 0 to the maximum number in the rand() function.
    //Time for the following process about 22 sec. on Ryzen 5 cpu.
    for (long i = 0; i < PRIMEMAX; i++){
        if(isPrimeRt(i) == 1) {
            str = (char *) calloc(numbers.strsize, sizeof(char));
            sprintf(str, "%ld", i);
            addString(&numbers, str);
        }
    }

    sem_wait(&filelock);

    if((fptr = fopen("prime.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        pthread_exit((void*)retval);
    }

    for (unsigned long int i = 0; i < numbers.used; i++){
        fprintf(fptr, "%s\n", numbers.array[i]);
    }

    fclose(fptr);
    sem_post(&primelock);
    sem_post(&filelock);
    freeArray(&numbers);

    retval = 1;
    data->end = clock();
    pthread_exit((void *) retval);
}

void * primeRd(void * t){
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();
    time_t t1;
    long retval = 0;
    long psize;
    Array numbers;
    initArray(&numbers, 2, 15);
    char * str;

    sem_wait(&primelock);
    sem_wait(&filelock);

    if((fptr = fopen("prime.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        pthread_exit((void*) retval);

    }
    while (!feof(fptr)){
        str = (char *) calloc(numbers.strsize, sizeof(char));
        fscanf(fptr,"%s",str);
        addString(&numbers, str);
    }


    fclose(fptr);
    sem_post(&primelock);
    sem_post(&filelock);

    int * primes = (int *) calloc(numbers.used, sizeof(int));
    for(unsigned long int i = 0; i < numbers.used; i++){
        char * tmp;
        primes[i] = strtol(numbers.array[i], &tmp, 10);
    }
    psize = numbers.used;
    freeArray(&numbers);

    srand((unsigned int) time(&t1));

    //using linear search to add a bit more processing time. Can be changed to binary search.
    retval = 0;
    for(int i = 0; i < 1000; i++){
        int random = rand() % PRIMEMAX;
        for (int j = 0; j < psize; j++){
            if (random == primes[j]){
                retval++;
            }
        }
    }

    free(primes);
    data->end = clock();
    pthread_exit((void *) retval);
}

void * fibonacciWr(void * t){
    sem_wait(&fibonaccilock);
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();
    long retval = 0;
    long n = RAND_MAX;

    Array numbers;
    initArray(&numbers, 2, 15);

    fibonacci(&numbers, 0, 1, n);


    sem_wait(&filelock);

    if((fptr = fopen("fibonnaci.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        pthread_exit((void*)retval);
    }

    for (unsigned long int i = 0; i < numbers.used; i++){
        fprintf(fptr, "%s\n", numbers.array[i]);
    }

    fclose(fptr);
    sem_post(&fibonaccilock);
    sem_post(&filelock);
    freeArray(&numbers);

    data->end = clock();
    retval = 1;
    pthread_exit((void *)retval);
}

void * fibonacciRd(void * t){
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();
    long retval = 0;
    long fnsize;
    time_t time1;
    Array numbers;
    int * fibnum;
    char * str;

    initArray(&numbers, 2, 15);

    sem_wait(&fibonaccilock);
    sem_wait(&filelock);

    if((fptr = fopen("fibonnaci.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        pthread_exit((void*) retval);

    }

    while (!feof(fptr)){
        str = (char *) calloc(numbers.strsize, sizeof(char));
        fscanf(fptr,"%s",str);
        addString(&numbers, str);
    }

    fclose(fptr);
    sem_post(&fibonaccilock);
    sem_post(&filelock);

    fibnum = (int *) calloc(numbers.used, sizeof(long));
    for(int i = 0; i < numbers.used; i++){
        char * tmp;
        fibnum[i] = strtol(numbers.array[i], &tmp, 10);
    }

    fnsize = numbers.used;
    freeArray(&numbers);
    srand((unsigned int) time(&time1));

    retval = 0;
    for(int i = 0; i < 1000000; i++){
        int random = rand();
        if(bisearch(fibnum, random, fnsize) >= 0){
            retval++;
        }
    }
    free(fibnum);
    data->end = clock();
    pthread_exit((void *) retval);

}

void * towerOfHanoiWr(void * t){
    sem_wait(&tohlock);
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();
    unsigned long int strsize = 100;
    Array ins;
    long retval = 0;
    int n = TOH_DISK;

    initArray(&ins, 2, strsize);

    towerOfHanoi(&ins, n, 'A', 'C', 'B');

    /*while(primelock == 1 || fibonaccilock == 1){

    }*/
    sem_wait(&filelock);

    if((fptr = fopen("toh.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        pthread_exit((void*)retval);
    }

    for (unsigned long int i = 0; i < ins.used; i++){
        fprintf(fptr, "%s\n", ins.array[i]);
    }

    sem_post(&tohlock);
    fclose (fptr);
    sem_post(&filelock);

    freeArray(&ins);

    data->end = clock();
    retval = 1;
    pthread_exit((void *) retval);
}

void * towerOfHanoiRd(void * t){
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();
    long retval = 0;
    int n = TOH_DISK;
    char * str;
    Array ins;
    initArray(&ins, 2, 100);

    sem_wait(&tohlock);
    sem_wait(&filelock);

    if((fptr = fopen("toh.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
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
    data->end = clock();
    pthread_exit((void *) retval);
}

int main() {
    int num_t = 6;
    void * (*fun_ptr_arr[])(void *) = {primeWr, primeRd, fibonacciWr, fibonacciRd, towerOfHanoiWr, towerOfHanoiRd};
    void * retval [num_t];
    double time_spent [num_t];
    double seq_total = 0;
    Thread_data data [num_t];

    pthread_attr_t attr;
    pthread_t threads [num_t];
    int rc, t;

    sem_init(&filelock, 0, 3);
    sem_init(&tohlock, 0, 1);
    sem_init(&fibonaccilock, 0, 1);
    sem_init(&primelock, 0, 1);

    //Create the joinable attributes for the threads.
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Create the threads
    for(t = 0; t < num_t; t++) {
        data[t].taskid = t;
        rc = pthread_create(&threads[t], &attr, fun_ptr_arr[t], (void *) &data[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    clock_t begin = clock();
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

    clock_t end = clock();

    double main_time = (double) (end - begin)/CLOCKS_PER_SEC;
    for (int i = 0; i < num_t; i++){
        if(i % 2 == 1){
            time_spent[i] = ((double) (data[i].end - data[i].start) / CLOCKS_PER_SEC) - time_spent[i-1];
        } else {
            time_spent[i] = (double) (data[i].end - data[i].start) / CLOCKS_PER_SEC;
        }
        seq_total += time_spent[i];
        printf("Thread %ld process time was %lf\n", data[i].taskid, time_spent[i]);
    }
    /*
     * For fair comparison between the total time without multithreading,
     * i have subtracted the writing time from the reader threads,
     * since they have to wait for writers to be done.*/

    printf("\nTime it took for all threads to join: %lf\n", main_time);
    printf("\nTime it would have taken without multithreading: %lf\n", seq_total);

    printf("\nPercentage difference between the two: %lf\n", 100-((main_time/seq_total)*100));
    
    sem_destroy(&filelock);
    sem_destroy(&tohlock);
    sem_destroy(&fibonaccilock);
    sem_destroy(&primelock);

    pthread_exit(NULL);

}