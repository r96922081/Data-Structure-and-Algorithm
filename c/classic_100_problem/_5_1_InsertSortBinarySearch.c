#include "Util.h"

static void CheckAnswer(ArrayList* src, int count) {
    int prev = -1;
    for (int i = 0; i < count; i++) {
        int value = src->Get(src, i);
        check(prev <= value);
        prev = value;
    }
}

void _5_1_InsertSortBinarySearch() {
    srand(time(NULL));

    int count = 20;
    ArrayList* src = NewArrayList();

    for (int i = 0; i < count; i++) {
        src->Append(src, rand() % 100 + 1);
    }

    src->Print(src);

    for (int i = 1; i < count; i++) {
        int value = src->Get(src, i);
        int left = 0;
        int right = i - 1;

        while (left <= right) {
            int middle = (left + right) / 2;
            if (src->Get(src, middle) == value) {
                left = middle;
                break;
            } else if (src->Get(src, middle) < value) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        memmove(src->data + (left + 1), src->data + left, sizeof(void*) * (i - left));
        src->Set(src, left, value);        
    }

    src->Print(src);

    CheckAnswer(src, count);
    DeleteArrayList(src);
}