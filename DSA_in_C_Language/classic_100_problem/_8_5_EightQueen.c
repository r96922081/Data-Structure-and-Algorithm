#include "Util.h"
#include "ArrayList.h"
#include "Matrix.h"

int CheckValidity(Matrix* matrix, int row, int column) {
    int row2 = row - 1;
    int column2 = column - 1;
    while (row2 >= 0 && column2 >= 0) {
        if (matrix->Get(matrix, row2, column2) == 1)
            return 0;
        row2--;
        column2--;
    }

    row2 = row - 1;
    column2 = column + 1;
    while (row2 >= 0 && column2 < 8) {
        if (matrix->Get(matrix, row2, column2) == 1)
            return 0;
        row2--;
        column2++;
    } 

    row2 = row - 1;
    while (row2 >= 0) {
        if (matrix->Get(matrix, row2, column) == 1)
            return 0;
        row2--;        
    } 

    return 1;
}

int Backtracking(Matrix* matrix, int row) {
    int count = 0;
    for (int column = 0; column < 8; column++) {
        if (CheckValidity(matrix, row, column) == 0)
            continue;


        matrix->Set(matrix, row, column, 1);
        if (row == 7) {
            matrix->Print(matrix);
            count++;
        }
        else 
            count += Backtracking(matrix, row + 1);
        matrix->Set(matrix, row, column, 0);
    }
    return count;
}

void _8_5_EightQueen() 
{
    Matrix* matrix = NewMatrix(8, 8);

    int count = Backtracking(matrix, 0);
    printf("count = %d\n", count);

    DeleteMatrix(matrix);
}