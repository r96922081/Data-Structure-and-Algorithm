#include "Util.h"
#include "Matrix.h"

static int GetNeighborCount(Matrix* m, int row, int col) {
    int count = 0;
    for (int diffRow = -1; diffRow <= 1; diffRow++) {
        for (int diffCol = -1; diffCol <= 1; diffCol++) {
            if (diffRow == 0 && diffCol == 0)
                continue;
                
            int newRow = row + diffRow;
            int newCol = col + diffCol;

            if (newRow < 0 || newRow >= m->row || newCol < 0 || newCol >= m->column)
                continue;
            
            if (m->Get(m, newRow, newCol) == 1)
                count++;
        }        
    }

    return count;
}

void _8_10_GameOfLife(int size, int iteration) {
    srand(time(NULL));

    Matrix* m = NewMatrix(size, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (rand() % 2 == 1) {
                m->Set(m, i, j, 1);
            }
        }
    }

    for (int i = 0; i < iteration; i++) {
        printf("Iteration #%d:\n\n", i);
        m->Print(m);
        printf("\n");
        Matrix* m2 = NewMatrix(size, size);
        
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                int neighborCount = GetNeighborCount(m, row, col);
                int v = m->Get(m, row, col);

                if (v == 1) {
                    if (neighborCount < 2) {
                        v = 0;
                    } else if (neighborCount < 4) {

                    } else {
                        v = 0;
                    }
                } else {
                    if (neighborCount == 3) {
                        v = 1;
                    }
                }
                m2->Set(m2, row, col, v);
            }
        }
        
        
        DeleteMatrix(m);
        m = m2;
    }
    
    DeleteMatrix(m);

    
}