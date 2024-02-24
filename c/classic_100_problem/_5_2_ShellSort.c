#include "Util.h"

static void CheckAnswer(ArrayList* src, int count) {
    int prev = -1;
    for (int i = 0; i < count; i++) {
        int value = src->Get(src, i);
        check(prev <= value);
        prev = value;
    }
}

void _5_2_ShellSort() {
    srand(time(NULL));

    int count = 20;
    ArrayList* src = NewArrayList();

    for (int i = 0; i < count; i++) {
        src->Append(src, rand() % 100 + 1);
    }

    src->Print(src);

    for (int gap = count/2; gap >= 1; gap /= 2) {
        for (int i = gap; i < count; i += gap) {
            int value = src->Get(src, i);
            int j = i - gap;
            for (; value < src->Get(src, j) && 0 <= j; j -= gap) {
                src->Set(src, j + gap, src->Get(src, j));
            }
            src->Set(src, j + gap, value);
        }
    }

    src->Print(src);

    CheckAnswer(src, count);
    DeleteArrayList(src);
}