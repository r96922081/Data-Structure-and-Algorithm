#include "Util.h"

static ArrayList* MergeSort(ArrayList* a, int start, int end) {
    ArrayList* ret = NewArrayList();
    if (start == end) {
        ret->Append(ret, a->Get(a, start));
        return ret;
    } 
    
    // split
    ArrayList* b = MergeSort(a, start, (start + end) / 2);
    ArrayList* c = MergeSort(a, (start + end) / 2 + 1, end);

    int bIndex = 0;
    int cIndex = 0;
    while (bIndex < b->size || cIndex < c->size) {
        int bValue = bIndex < b->size? b->Get(b, bIndex) : 1000000;
        int cValue = cIndex < c->size? c->Get(c, cIndex) : 1000000;

        if (bValue <= cValue) {
            ret->Append(ret, bValue);
            bIndex++;
        } else {
            ret->Append(ret, cValue);
            cIndex++;
        }
    }

    DeleteArrayList(b);
    DeleteArrayList(c);

    return ret;
}

void _5_9_MergeSort() {
    srand(time(NULL));
    int n = 20;
    ArrayList* a = NewArrayList();

    for (int i = 0; i < n; i++) {
        a->Append(a, rand() % 100 + 1);
    }

    a->Print(a);
    
    ArrayList* b = MergeSort(a, 0, n - 1);

    b->Print(b);

    DeleteArrayList(a);   
    DeleteArrayList(b);   
}