#include "Matrix.h"
#include "LinkedList.h"
#include "Util.h"

static LinkedList* _8_7_HamiltonCycle_main(Matrix* m);
/*
(0)--(1)--(2)
 |   / \   |
 |  /   \  | 
 | /     \ |
(3)-------(4)
*/
static void _8_7_HamiltonCycle_1() {
    Matrix* m = NewMatrix(5, 5);
    m->Set(m, 0, 1, 1);
    m->Set(m, 0, 3, 1);
    m->Set(m, 1, 0, 1);
    m->Set(m, 1, 2, 1);
    m->Set(m, 1, 3, 1);
    m->Set(m, 1, 4, 1);
    m->Set(m, 2, 1, 1);
    m->Set(m, 2, 4, 1);
    m->Set(m, 3, 0, 1);
    m->Set(m, 3, 1, 1);
    m->Set(m, 3, 4, 1);
    m->Set(m, 4, 1, 1);
    m->Set(m, 4, 2, 1);
    m->Set(m, 4, 3, 1);

    _8_7_HamiltonCycle_main(m);

    DeleteMatrix(m);
}

/*
(0)--(1)--(2)
 |   / \   |
 |  /   \  | 
 | /     \ |
(3)      (4)
*/
static void _8_7_HamiltonCycle_2() {
    Matrix* m = NewMatrix(5, 5);
    m->Set(m, 0, 1, 1);
    m->Set(m, 0, 3, 1);
    m->Set(m, 1, 0, 1);
    m->Set(m, 1, 2, 1);
    m->Set(m, 1, 3, 1);
    m->Set(m, 1, 4, 1);
    m->Set(m, 2, 1, 1);
    m->Set(m, 2, 4, 1);
    m->Set(m, 3, 0, 1);
    m->Set(m, 3, 1, 1);
    m->Set(m, 4, 1, 1);
    m->Set(m, 4, 2, 1);

    _8_7_HamiltonCycle_main(m);

    DeleteMatrix(m);    
}

void _8_7_HamiltonCycle() {
    _8_7_HamiltonCycle_1();
    _8_7_HamiltonCycle_2();
}

static void _8_7_HamiltonCycle_main2(Matrix* m, int startNode, int currentNode, int* selected, LinkedList* answer) {
    if (selected[currentNode] != 0)
        return;

    selected[currentNode] = 1;
    answer->Append(answer, currentNode);

    if (answer->size == m->column && m->Get(m, currentNode, startNode) == 1) {
        answer->Append(answer, startNode);
        return;
    }

    for (int nextNode = 0; nextNode < m->column; nextNode++) {
        if (m->Get(m, currentNode, nextNode) == 1 && selected[nextNode] == 0) {
            _8_7_HamiltonCycle_main2(m, startNode, nextNode, selected, answer);
        }
    }

    if (answer->size == m->column + 1) {
        return;
    }

    answer->Delete(answer, answer->tail);
    selected[currentNode] = 0;    
}

static LinkedList* _8_7_HamiltonCycle_main(Matrix* m) {
    printf("Graph:\n");

    int count = m->column;
    int* selected = calloc(1, sizeof(int));
    LinkedList* answer = NewLinkedList();

    _8_7_HamiltonCycle_main2(m, 0, 0, selected, answer);

    m->Print(m);
    if (answer->size != count + 1)
        printf("No Solution\n");
    else {
        answer->Print(answer);
    }

    DeleteLinkedList(answer);
    free(selected);
}