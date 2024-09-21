#include "Matrix.h"
#include "Stack.h"

typedef struct Step {
    int selection;
    int row;
    int col;
    int rank;
} Step;

static Step* NewStep(int selection, int row, int col, int rank) {
    Step* s = malloc(sizeof(Step));
    s->selection = selection;
    s->row = row;
    s->col = col;
    s->rank = rank;
}

static int nextRowDiff[] = {-2, -1, 1, 2, 2, 1, -1, -2};
static int nextColDiff[] = {1, 2, 2, 1, -1, -2, -2, -1};

static int valid(Matrix* m, int row, int col) {
    if (row < 0 || col < 0 || row >= m->row || col >= m->column)
        return 0;

    if (m->Get(m, row, col) != 0)
        return 0;

    return 1;
}

void _8_6_KnightTour(int rowCount, int colCount) {
    Matrix* m = NewMatrix(rowCount, colCount);
    Stack* stack = NewStack();
    int foundSolution = 0;

    Step* s = NewStep(0, 0, 0, 1);
    stack->Push(stack, s); 

    while(!stack->IsEmpty(stack) && !foundSolution) 
    { 
        s = stack->Pop(stack);

        m->Set(m, s->row, s->col, s->rank);

        if (s->rank == rowCount * colCount) {
            free(s);
            foundSolution = 1;
            break;
        }

        int foundNext = 0;
        for (int i = s->selection; i < 8; i++) {
            int nextRow = s->row + nextRowDiff[i];
            int nextCol = s->col + nextColDiff[i];
            if (valid(m, nextRow, nextCol)) {
                foundNext = 1;
                s->selection = i + 1;
                stack->Push(stack, s);
                Step* s2 = NewStep(0, nextRow, nextCol, s->rank + 1);
                stack->Push(stack, s2); 
                break;
            }                
        }

        if (!foundNext) {
            m->Set(m, s->row, s->col, 0);
            free(s);            
        }
    }

    while (stack->IsEmpty(stack) == 0) {
        Step* s = stack->Pop(stack);
        free(s);
    }

    if (foundSolution)
        m->Print(m);
    else
        printf("rowCount = %d, colCount = %d, has no solution\n", rowCount, colCount);

    DeleteStack(stack);
    DeleteMatrix(m);
}