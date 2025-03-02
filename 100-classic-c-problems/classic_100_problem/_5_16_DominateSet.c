#include "Util.h"

static void Print(void* v) {
    Point* p = v;
    printf("(%d, %d)", p->x, p->y);
}

static int sortFunction(void* a, void* b) {
    Point* p1 = a;
    Point* p2 = b;

    if (p1->x < p2->x)
        return -1;
    else if (p1->x == p2->x) {
        if (p1->y == p2->y)
            return 0;
        else if (p1->y < p2->y)
            return -1;
        else
            return 1;
    } else {
        return 1;
    }
}

void _5_16_DominateSet() {
    ArrayList* a = NewArrayList();

    a->Append(a, NewPoint(0,0));
    a->Append(a, NewPoint(1,1));
    a->Append(a, NewPoint(3,0));
    a->Append(a, NewPoint(2,1));
    a->Append(a, NewPoint(1,3));
    a->Append(a, NewPoint(0,1));

    a->Print2(a, Print);
    a->Sort(a, sortFunction);
    a->Print2(a, Print);

    int maxY = -1;

    for (int i = a->size - 1; i >=0; i--) {
        Point* p = a->Get(a, i);
        if (p->y >= maxY) {
            Print(p);
            printf("\n");
            maxY = p->y;
        }
    }


    DeleteArrayListAndElement(a);
}