#include "Util.h"

static int compareFunction(const void* i, const void* j) {
    return (int)i - (int)j;
}

void _5_11_SingleDuplicate() {
    int a[] = {3, 7, 3, 3, 4, 3, 3, 3, 3, 3, 3, 9, 3, 3, 3, 3};

    int prev = -1;
    int duplicate = -1;
    
    for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
        int v = a[i];
        if (v == prev) {
            duplicate = v;
            break;
        } else {
            prev = v;
        }
    }

    ArrayList* list = NewArrayList();
    int duplicateCount = 0;
    for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
        int v = a[i];
        if (v != duplicate) {
            list->Append(list, v);
        } else {
            if (duplicateCount == 0) {
                list->Append(list, duplicate);
            }
            duplicateCount++;
        }
    }

    list->Sort(list, compareFunction);

    for (int i = 0; i < list->size; i++)
    {
        if (i != 0)
            printf(", ");
        int v = list->Get(list, i);
        printf("%d", v);
        if (v == duplicate)
            for (int j = 0; j < duplicateCount - 1; j++)
                printf(", %d", duplicate);
    }

    printf("\n");

    DeleteArrayList(list);
}