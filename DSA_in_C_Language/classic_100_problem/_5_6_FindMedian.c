#include "Util.h"

static int compareFunction(const void* i, const void* j) {
    return (int)i - (int)j;
}

static int GetMedian(ArrayList* src) {
    ArrayList* src2 = NewArrayList();
    for (int i = 0; i < src->size; i++)
        src2->Append(src2, src->Get(src, i));

    src2->Sort(src2, compareFunction);
    int ret = src2->Get(src2, src2->size / 2);
    DeleteArrayList(src2);
    return ret;
    
}

void _5_6_FindMedian() {
    for (int testCount = 0; testCount < 1; testCount++) {
        int seed = testCount * 100;
        srand(seed);

        int count = 7;
        ArrayList* src = NewArrayList();
        

        for (int i = 0; i < count; i++) {
            src->Append(src, rand() % 10 + 1);
        }
        src->Print(src);
        int answer = GetMedian(src);

        int targetPos = count / 2;
        int left = 0;
        int right = count - 1;    
        int pivotPos = -1;

        while (pivotPos != targetPos) {
            if (pivotPos < targetPos) {
                left = pivotPos + 1;
            } else {
                right = pivotPos - 1;
            }
            int pivotValue = src->Get(src, left);

            int left2 = left;
            int right2 = right;

            while (left2 < right2) {
                for (;src->Get(src, left2) <= pivotValue; left2++)
                    ;
                for (;pivotValue < src->Get(src, right2); right2--)
                    ;

                if (left2 < right2) {
                    int temp = src->Get(src, left2);
                    src->Set(src, left2, src->Get(src, right2));
                    src->Set(src, right2, temp);
                }
            }

            pivotPos = right2;
            int temp = src->Get(src, left);
            src->Set(src, left, src->Get(src, pivotPos));            
            src->Set(src, pivotPos, temp);
        }

        int median = src->Get(src, targetPos);
        printf("median = %d\n", median);
        check(answer == median);
        DeleteArrayList(src);
    }
}