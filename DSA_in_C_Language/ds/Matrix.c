#include "Matrix.h"
#include "ArrayList.h"

Matrix* NewMatrix(int rowCount, int columnCount);
void DeleteMatrix(Matrix* matrix);

static void Print(Matrix*);
static void Set(Matrix* matrix, int row, int column, void* value);
static void* Get(Matrix* matrix, int row, int column);

Matrix* NewMatrix(int rowCount, int columnCount) {
    Matrix* matrix = calloc(1, sizeof(Matrix));
    matrix->row = rowCount;
    matrix->column = columnCount;
    matrix->list = NewArrayList();

    for (int i = 0; i < rowCount; i++) {
        ArrayList* row = NewArrayList();
        for (int j = 0; j < columnCount; j++) {
            row->Append(row, 0);
        }
        matrix->list->Append(matrix->list, row);
    }        
    matrix->Get = Get;
    matrix->Set = Set;
    matrix->Print = Print;

    return matrix;
}

static void Print(Matrix* matrix) {
    for (int i = 0; i < matrix->row; i++) {
        ArrayList* row = matrix->list->Get(matrix->list, i);
        printf("%d", row->Get(row, 0));
        for (int j = 1; j < matrix->column; j++) {
            printf(",%d", row->Get(row, j));
        }
        printf("\n");
    }
    printf("\n");
}

static void Set(Matrix* matrix, int rowIndex, int column, void* value) {
    ArrayList* row = matrix->list->Get(matrix->list, rowIndex);
    row->Set(row, column, value);
}

static void* Get(Matrix* matrix, int rowIndex, int column) {
    ArrayList* row = matrix->list->Get(matrix->list, rowIndex);
    return row->Get(row, column);
}

void DeleteMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->row; i++) {
        ArrayList* row = matrix->list->Get(matrix->list, i);
        DeleteArrayList(row);
    }
    DeleteArrayList(matrix->list);
    free(matrix);
}