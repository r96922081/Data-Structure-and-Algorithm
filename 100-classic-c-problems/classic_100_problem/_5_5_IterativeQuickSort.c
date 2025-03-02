#include "Util.h"
#include "ArrayList.h"

static void pivot(ArrayList* src, int left, int right, int* fixed) {
    int pivotValue = src->Get(src, left);
    int originalLeft = left;

    while (left < right) {
        while (left < src->size && src->Get(src, left) <= pivotValue) {
            left++;
        }

        while ( 0 <= right && pivotValue < src->Get(src, right)) {
            right--;
        }

        if (left < right) {
            int temp = src->Get(src, left);
            src->Set(src, left, src->Get(src, right));
            src->Set(src, right, temp);
        }

    }

    src->Set(src, originalLeft, src->Get(src, right));
    src->Set(src, right, pivotValue);
    fixed[right] = 1;
}

void _5_5_IterativeQuickSort() {
    srand(time(NULL));

    int count = 20;
    ArrayList* src = NewArrayList();
    int* fixed = calloc(sizeof(int), count);

    for (int i = 0; i < count; i++) {
        src->Append(src, rand() % 100 + 1);
    }

    src->Print(src);
    
    int left = 0;
    while (left < count) {
        int right = left + 1;
        for (; right < count; right++) {
            if (fixed[right] == 1)
                break;
        }
        right--;
        pivot(src, left, right, fixed);
        while (left < count && fixed[left] == 1) {
            left++;
        }
    }

    src->Print(src);
    DeleteArrayList(src);
    free(fixed);
}