#ifndef MATRIX_H
#define MATRIX_H

#include "ArrayList.h"

typedef struct Matrix Matrix;

typedef struct Matrix {
    ArrayList* list;
    int row;
    int column;
    void (*Print)(Matrix*);
    void (*Set)(Matrix* matrix, int row, int column, void* value);
    void* (*Get)(Matrix* matrix, int row, int column);
} Matrix;

Matrix* NewMatrix(int rowCount, int columnCount);
void DeleteMatrix(Matrix* matrix);

#endif