#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "functions.h"
#include "dynamicarray.h"
#include <string.h>

#define TOH_DISK 20 // Number of disk used in tower of hanoi, number of instructions = 2 ^ TOH_DISK
#define PRIMEMAX 10000000 // Prime numbers are being found up to PRIMEMAX

typedef struct {
    long taskid;
    clock_t start;
    clock_t end;
} Thread_data;

//Global variables
FILE * fptr;
sem_t filelock;
sem_t primelock;
sem_t fibonaccilock;
sem_t tohlock;

/*
 * Finds the primenumbers up to PRIMEMAX, and writes them into a file.
 * File name: prime.txt
 * returns 1 if successful
 * returns -1 if unable to open file.
 */
void * primeWr(void * t){
    //Lock the primeRd thread, so it waits for this thread to be done writing.
    sem_wait(&primelock);

    // Initialization phase.

    // start gathering timing data.
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

    //Wait until file is open for writing.
    sem_wait(&filelock);

    // Open the file and write to it.
    if((fptr = fopen("prime.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        data->end = clock();
        pthread_exit((void*)retval);
    }

    for (unsigned long int i = 0; i < numbers.used; i++){
        fprintf(fptr, "%s\n", numbers.array[i]);
    }

    fclose(fptr);

    //Free the locks and variables.
    sem_post(&primelock);
    sem_post(&filelock);
    freeArray(&numbers);

    //Set return value and set process end time.
    retval = 1;
    data->end = clock();
    pthread_exit((void *) retval);
}

/*
 * Thread to read the prime numbers from file, and generate random numbers and figure out if they are primenumbers.
 * File name: prime.txt
 * Returns number of random generated primenumbers
 * Returns -1 if failing to open the file.
 */
void * primeRd(void * t){

    // Initialization phase.

    // start gathering timing data.
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();

    time_t t1;
    long retval = 0;
    long psize;
    Array numbers;
    initArray(&numbers, 2, 15);
    char * str;

    // Wait for the primeWr thread to be done, and for the file to be unused.
    sem_wait(&primelock);
    sem_wait(&filelock);

    //Open the file and read the data into an dynamic array.
    if((fptr = fopen("prime.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        data->end = clock();
        pthread_exit((void*) retval);

    }

    while (!feof(fptr)){
        str = (char *) calloc(numbers.strsize, sizeof(char));
        fscanf(fptr,"%s",str);
        addString(&numbers, str);
    }


    fclose(fptr);

    //Free the locks, for others to use.
    sem_post(&primelock);
    sem_post(&filelock);


    //Convert the strings to integers.
    int * primes = (int *) calloc(numbers.used, sizeof(int));
    for(unsigned long int i = 0; i < numbers.used; i++){
        char * tmp;
        primes[i] = strtol(numbers.array[i], &tmp, 10);
    }
    psize = numbers.used;

    //Free the dynamic array.
    freeArray(&numbers);

    //Seed the RNG.
    srand((unsigned int) time(&t1));

    //Create a number of random numbers and figure out if they are primenumbers.
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

    // Free the variables and get the end process time.
    free(primes);
    data->end = clock();
    pthread_exit((void *) retval);
}

/*
 * Creates the fibonacci sequence of numbers and writes them into a text file.
 * File name: fibonacci.txt
 * Returns 1 if successful
 * Returns -1 if failed to open the file.
 */

void * fibonacciWr(void * t){
    // Locks the fibonacciRd thread, so it waits for the writer to be done.
    sem_wait(&fibonaccilock);

    // Initialization phase.

    // start gathering timing data.
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();

    long retval = 0;
    long n = RAND_MAX;
    Array numbers;
    initArray(&numbers, 2, 15);

    // Create the fibonacci sequence of numbers using recursion.
    fibonacci(&numbers, 0, 1, n);

    // Lock the file for use by this thread.
    sem_wait(&filelock);

    // Open the file and write the sequence of numbers into it.
    if((fptr = fopen("fibonnaci.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        data->end = clock();
        pthread_exit((void*)retval);
    }

    for (unsigned long int i = 0; i < numbers.used; i++){
        fprintf(fptr, "%s\n", numbers.array[i]);
    }

    fclose(fptr);

    //Free the locks and the dynamic array.
    sem_post(&fibonaccilock);
    sem_post(&filelock);
    freeArray(&numbers);

    // Get end time and return.
    data->end = clock();
    retval = 1;
    pthread_exit((void *)retval);
}

/*
 * Thread to read an fibonacci sequence of numbers from a file, and generate random numbers and figure out if they are a part of the sequence
 * File name: fibonacci.txt
 * Returns number of fibonacci numbers randomly generated.
 * Returns -1 if failed to open the file.
 */
void * fibonacciRd(void * t){

    // Initialization phase.

    // start gathering timing data.
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

    // Wait for the fibonacciWr thread to be done, and for the file to be unused.
    sem_wait(&fibonaccilock);
    sem_wait(&filelock);

    // Open the file and read the data into an dynamic array.
    if((fptr = fopen("fibonnaci.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        data->end = clock();
        pthread_exit((void*) retval);

    }

    while (!feof(fptr)){
        str = (char *) calloc(numbers.strsize, sizeof(char));
        fscanf(fptr,"%s",str);
        addString(&numbers, str);
    }

    fclose(fptr);

    // Free the locks
    sem_post(&fibonaccilock);
    sem_post(&filelock);

    // Convert the strings into an array of integers.
    fibnum = (int *) calloc(numbers.used, sizeof(long));
    for(int i = 0; i < numbers.used; i++){
        char * tmp;
        fibnum[i] = strtol(numbers.array[i], &tmp, 10);
    }

    fnsize = numbers.used;

    // Free the dynamic array of strings.
    freeArray(&numbers);

    //Seed the RNG.
    srand((unsigned int) time(&time1));

    // Generate random numbers and figure out if they are fibonacci numbers.
    retval = 0;
    for(int i = 0; i < 1000000; i++){
        int random = rand();
        if(bisearch(fibnum, random, fnsize) >= 0){
            retval++;
        }
    }
    // Free heap data and get the end process time.
    free(fibnum);
    data->end = clock();
    pthread_exit((void *) retval);

}

void * towerOfHanoiWr(void * t){
    // Locks the fibonacciRd thread, so it waits for the writer to be done.
    sem_wait(&tohlock);

    // Initialization phase.

    // start gathering timing data.
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();

    unsigned long int strsize = 100;
    Array ins;
    long retval = 0;
    int n = TOH_DISK;

    initArray(&ins, 2, strsize);

    // Run tower of hanoi function to get an list of instruction for the tower of hanoi player.
    // Uses recursion to generate the list.
    towerOfHanoi(&ins, n, 'A', 'C', 'B');

    //Lock the file, so it can be used for writing.
    sem_wait(&filelock);

    // Open the file and write the list of instructions into the file.
    if((fptr = fopen("toh.txt", "w")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        data->end = clock();
        pthread_exit((void*)retval);
    }

    for (unsigned long int i = 0; i < ins.used; i++){
        fprintf(fptr, "%s\n", ins.array[i]);
    }


    fclose (fptr);

    //Free the locks.
    sem_post(&tohlock);
    sem_post(&filelock);

    //Free array of strings and get the end time.
    freeArray(&ins);

    data->end = clock();
    retval = 1;
    pthread_exit((void *) retval);
}

/*
 * Thread reads an list of instructions, and solves an tower of hanoi.
 * Returns 1 if it could use the instruction to solve the tower.
 * Returns 0 if it could not solve the tower using the instructions.
 * Returns -1 if it could not open the file.
 */
void * towerOfHanoiRd(void * t){

    // Initialization phase.

    // start gathering timing data.
    Thread_data * data = (Thread_data *) t;
    printf("Starting thread %ld\n", data->taskid);
    data->start = clock();

    long retval = 0;
    int n = TOH_DISK;
    char * str;
    Array ins;
    initArray(&ins, 2, 100);

    //Wait for the towerOfHanoiWr to be done writing the instructions into the file.
    sem_wait(&tohlock);
    sem_wait(&filelock);

    //Open the file, and read the data into an dynamic array of strings.
    if((fptr = fopen("toh.txt", "r")) == NULL) {
        puts("File couldn't be opened");
        retval = -1;
        data->end = clock();
        pthread_exit((void*) retval);

    }

    while (!feof(fptr)){
        str = (char *) calloc(ins.strsize, sizeof(char));
        fgets(str, ins.strsize, fptr);
        addString(&ins, str);
    }

    fclose(fptr);

    // Free the locks.
    sem_post(&tohlock);
    sem_post(&filelock);

    //Solve the tower of Hanoi, using the list of instructions.
    retval = tOHPlayer(&ins, n);

    //Free the array, and get the end time.
    freeArray(&ins);
    data->end = clock();
    pthread_exit((void *) retval);
}

int main() {

    // Initialization phase

    int num_t = 6;

    // Using an list of function pointers to pass to the thread creater.
    void * (*fun_ptr_arr[])(void *) = {primeWr, primeRd, fibonacciWr, fibonacciRd, towerOfHanoiWr, towerOfHanoiRd};

    void * retval [num_t];
    double time_spent [num_t];
    double seq_total = 0;
    Thread_data data [num_t];

    pthread_attr_t attr;
    pthread_t threads [num_t];
    int rc, t;

    // Initialize the locks for the use of the threads.
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
    // Get the time from the creation of all threads, to the time it takes for them all to join.
    clock_t begin = clock();

    //Free attribute and wait for the other threads
    pthread_attr_destroy(&attr);

    //Wait for the threads to join.
    for (t = 0; t < num_t; t++){
        rc = pthread_join(threads [t], &retval[t]);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Value returned from thread %d: %ld\n", t, (long) retval[t]);
    }

    clock_t end = clock();

    // Calculate the processing times of the individual threads.

    double main_time = (double) (end - begin)/CLOCKS_PER_SEC;
    for (int i = 0; i < num_t; i++){
        if(i % 2 == 1){
            time_spent[i] = ((double) (data[i].end - data[i].start) / CLOCKS_PER_SEC) - time_spent[i-1];
        } else {
            time_spent[i] = (double) (data[i].end - data[i].start) / CLOCKS_PER_SEC;
        }
        seq_total += time_spent[i];
        printf("Thread %ld process time was %lf sec.\n", data[i].taskid, time_spent[i]);
    }

    /*
     * For fair comparison between the total time without multithreading,
     * i have subtracted the writing time from the reader threads,
     * since they have to wait for writers to be done.*/

    printf("\nTime it took for all threads to join: %lf sec.\n", main_time);
    printf("\nTime it would have taken without multithreading: %lf sec.\n", seq_total);

    printf("\nPercentage difference between the two: %lf %%\n", 100-((main_time/seq_total)*100));

    //Remember to destroy all the semaphores before ending the main.
    sem_destroy(&filelock);
    sem_destroy(&tohlock);
    sem_destroy(&fibonaccilock);
    sem_destroy(&primelock);

    pthread_exit(NULL);

}