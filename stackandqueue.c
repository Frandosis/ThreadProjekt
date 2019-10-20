//
// Created by Valdemar Landberg on 19-10-2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "stackandqueue.h"

void stackInit (Stack * s, int size){

    s->stack = (int *) calloc(size, sizeof(int));
    s->top = -1;
    s->size = size;
}

int sIsEmpty(Stack * s){
    if(s->top == -1){
        return 1;
    }
    return 0;
}

int sIsFull(Stack * s){
    if (s->top == s->size - 1){
        return 1;
    }
    return 0;
}

int sSize(Stack * s){
    return s->top+1;
}

int sPeek(Stack * s){
    return s->stack[s->top];
}

/* Pushes and integer unto the stack
 * returns 1 when successful
 * returns 0 when stack is full.
 * */
int sPush(Stack * s, int element){
    if (sIsFull(s) != 1){
        s->top += 1;
        s->stack[s->top] = element;
        return 1;
    }
    return 0;
}

/*Pop the top element of the stack
 * removes the element at the top.
 * NB. Peek before popping.
 * returns 1 when successful.
 * returns 0 when empty
 */
int sPop (Stack * s){
    if(sIsEmpty(s) != 1){
        s->top -= 1;
        return 1;
    }
    return 0;
}

void sFree (Stack * s){
    free(s->stack);
    s->top = -1;
    s->size = 0;
}

void queueInit (Queue * q, int size){
    q->queue = (int *) calloc (size, sizeof(int));
    q->max = size;
    q->size = 0;
    q->head = 0;
    q->tail = -1;
}

int qPeek (Queue * q){
    return q->queue[q->head];
}

int qIsEmpty (Queue * q){
    if (q->size == 0){
        return 1;
    }
    return 0;
}

int qIsFull(Queue * q){
    if (q->size == q->max){
        return 1;
    }
    return 0;
}

int qSize(Queue * q){
    return q->size;
}
/*
 * Insertion into the tail of the queue.
 * return 1 when succesful;
 * return 0 when failed;
 */
int qInsert(Queue * q, int element){

    if (qIsFull(q) != 1) {
        if (q->tail == q->max -1){
            q->tail = -1;
        }
        q->queue[++q->tail] = element;

    }
    return 0;
}

/* Removes the element at the head.
 * NB. Peek before removing.
 * returns 1 when successful.
 * returns 0 when removing an empty.
 */
int qRemove(Queue * q){
    if(qIsEmpty(q) != 1){
        q->head++;
        if(q->head == q->max) {
            q->head = 0;
        }

        q->size--;
        return 1;
    }
    return 0;
}

void qFree (Queue * q){
    free(q->queue);
    q->max = 0;
    q->size = 0;
    q->head = 0;
    q->tail = -1;
}


