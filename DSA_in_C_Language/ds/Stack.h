#ifndef STACK_H
#define STACK_H

#include "Util.h"

typedef struct Stack Stack;

typedef struct Stack {
    LinkedList* list;
    void (*Push)(Stack*, void*);
    void* (*Peek)(Stack*);
    void* (*Pop)(Stack*);
    int (*IsEmpty)(Stack*);
    int (*GetSize)(Stack*);
    void (*PrintFromTopToBottom)(Stack*);
    void (*PrintFromBottomToTop)(Stack*);
} Stack;

Stack* NewStack();
void DeleteStack(Stack*);


#endif