#include "Util.h"

static void heapify(ArrayList* a) {
    for (int i = (a->size - 2) / 2; i >= 0; i--) {
        int parent = i;
        while (1) {
            int value = a->Get(a, parent);        
            int left = i * 2 + 1;
            int right = i * 2 + 2;

            int leftValue = a->Get(a, left);
            int rightValue = 1000000;
            if (right < a->size ) {
                rightValue = a->Get(a, right);
            }

            int minChild = left;
            if (rightValue < leftValue) {
                minChild = right;
            }
            int minChildValue = a->Get(a, minChild);

            if (minChildValue < value) {
                a->Set(a, parent,  minChildValue);
                a->Set(a, minChild, value);
            }
            if (parent == 0)
                break;

            parent /= 2;
        }
    }
}

static ArrayList* HeapSort(ArrayList* a) {
    ArrayList* b = NewArrayList();

    for (int heapSize = a->size; heapSize != 0; heapSize--) {
        b->Append(b, a->Get(a, 0));

        a->Set(a, 0, a->Get(a, heapSize - 1));
        int parent = 0;
        while (1) {
            int parentValue = a->Get(a, parent);
            int left = parent * 2 + 1;
            int right = parent * 2 + 2;

            int leftValue = 10000000; 
            if (left < heapSize)
                leftValue = a->Get(a, left);
            int rightValue = 10000000;
            if (right < heapSize)
                rightValue = a->Get(a, right);
            
            int minChild = left;
            int minValue = leftValue;
            if (rightValue < leftValue) {
                minChild = right;
                minValue = rightValue;
            }

            if (parentValue < minValue)
                break;

            a->Set(a, parent, minValue);
            a->Set(a, minChild, parentValue);
            parent = minChild;
        }

    }
    
    return b;
}

void _5_7_HeapSort() {
    srand(time(NULL));
    int n = 20;

    // zero-based
    ArrayList* a = NewArrayList();

    for (int i = 0; i < n; i++) {
        a->Append(a, rand() % 100 + 1);
    }

    a->Print(a);

    heapify(a);
    
    ArrayList* b = HeapSort(a);

    b->Print(b);

    DeleteArrayList(a);    
    DeleteArrayList(b);  
}