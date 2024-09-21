#ifndef UTIL_H
#define UTIL_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "assert.h"
#include "string.h"
#include "math.h"

#include "LinkedList.h"
#include "ArrayList.h"
#include "Matrix.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "String.h"

void check(int ret);

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Pair {
    void* first;
    void* second;
} Pair;

typedef struct Triple {
    void* first;
    void* second;
    void* third;
} Triple;

Point* NewPoint(int x, int y);
Pair* NewPair(void* first, void* second);

#endif