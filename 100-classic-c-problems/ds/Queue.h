#ifndef QUEUE_H
#define QUEUE_H

#include "Util.h"

typedef struct Queue Queue;

typedef struct Queue {
    LinkedList* list;
    void (*Enqueue)(Queue*, void*);
    void* (*Dequeue)(Queue*);
    void* (*Peek)(Queue*);
    int (*IsEmpty)(Queue*);
    int (*GetSize)(Queue*);
} Queue;

Queue* NewQueue();
void DeleteQueue(Queue*);

#endif