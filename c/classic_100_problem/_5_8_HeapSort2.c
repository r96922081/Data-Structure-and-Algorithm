#include "math.h"
#include "Util.h"

static void CheckAnswer(ArrayList* src, int count) {
    int prev = -1;
    for (int i = 0; i < count; i++) {
        int value = src->Get(src, i);
        check(prev <= value);
        prev = value;
    }
}

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

static int GetLevel(int index) {
    return sqrt(index + 1);
}

static int GetIndex(int minChild, int level) {
    int minLevel = GetLevel(minChild);
    int value = minChild;
    for (; minLevel > level; minLevel--) {
        value = (value - 1) / 2;
    }
    return value;
}

static ArrayList* HeapSort(ArrayList* a) {
    ArrayList* b = NewArrayList();

    for (int heapSize = a->size; heapSize != 0; heapSize--) {
        b->Append(b, a->Get(a, 0));

        if (heapSize == 1)
            break;

        int valueToInsert = a->Get(a, heapSize - 1);
        int minChild = 0;
        int left = minChild * 2 + 1;
        int right = minChild * 2 + 2;

        while(left < heapSize - 1) {
            int leftValue = a->Get(a, left);
            int rightValue = 1000000;
            if (right < heapSize - 1)
                rightValue = a->Get(a, right);
            if (leftValue <= rightValue)
                minChild = left;
            else
                minChild = right;
            left = minChild * 2 + 1;
            right = minChild * 2 + 2;                
        }

        // binary search        
        int leftLevel = 1;
        int rightLevel = GetLevel(minChild);
        int middleLevel = (leftLevel + rightLevel) / 2;
        int minChildLevel = rightLevel;
        
        while (leftLevel <= rightLevel) {
            int middleValue = a->Get(a, GetIndex(minChild, middleLevel));
            if (middleValue <= valueToInsert) {
                if (middleLevel < minChildLevel && valueToInsert <= a->Get(a, GetIndex(minChild, middleLevel + 1))) {
                    break;
                }
                if (middleLevel == minChildLevel) {
                    if (valueToInsert < middleValue) {
                        middleLevel -= 1;
                    }
                    break;
                }

                leftLevel = middleLevel + 1;
            } else {
                rightLevel = middleLevel - 1;
            }
            middleLevel = (leftLevel + rightLevel) / 2;
        }

        // move up
        int indexToMoveUp = GetIndex(minChild, middleLevel);
        int temp = a->Get(a, indexToMoveUp);
        int temp2 = -1;
        for (int index = indexToMoveUp; index != 0; index = (index - 1) / 2) {  
            temp2 = a->Get(a, (index - 1) / 2);        
            a->Set(a, (index - 1) / 2, temp);
            temp = temp2;
        }

        a->Set(a, indexToMoveUp, valueToInsert);
    }
    
    return b;
}

void _5_8_HeapSort2() {
    for (int testCount = 0; testCount < 1; testCount++) {
        srand(time(NULL));
        int n = 10;

        // zero-based
        ArrayList* a = NewArrayList();

        for (int i = 0; i < n; i++) {
            a->Append(a, rand() % 10 + 1);
        }

        a->Print(a);

        heapify(a);
        
        ArrayList* b = HeapSort(a);

        b->Print(b);

        CheckAnswer(b, n);

        DeleteArrayList(a);    
        DeleteArrayList(b); 
        printf("\n");
    }
}