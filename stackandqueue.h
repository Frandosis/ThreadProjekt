//
// Created by Valdemar Landberg on 19-10-2019.
//

#ifndef THREADPROJEKT_STACKANDQUEUE_H
#define THREADPROJEKT_STACKANDQUEUE_H
typedef struct {
    int * stack;
    int top;
    int size;

} Stack;

void stackInit (Stack * s, int size);
int sIsEmpty(Stack * s);
int sIsFull(Stack * s);
int sPeek(Stack * s);
int sPush(Stack * s, int element);
int sPop (Stack * s);
void sFree (Stack * s);

typedef struct {
    int * queue;
    int head;
    int tail;
    int size;
    int max;
} Queue;

void queueInit (Queue * q, int size);
int qPeek (Queue * q);
int qIsEmpty (Queue * q);
int qIsFull(Queue * q);
int qSize(Queue * q);
int qInsert(Queue * q, int element);
int qRemove(Queue * q);
void qFree (Queue * q);

#endif //THREADPROJEKT_STACKANDQUEUE_H
