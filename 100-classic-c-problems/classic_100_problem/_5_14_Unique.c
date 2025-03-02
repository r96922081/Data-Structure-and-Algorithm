#include "Util.h"

static int compareFunction(const void* i, const void* j) {
    return (int)i - (int)j;
}

void _5_14_Unique() {
    srand(time(NULL));

    int count = 10;

    ArrayList* list = NewArrayList();

    for (int i = 0; i < count; i++)
        list->Append(list, rand() % 4);

    list->Print(list);
    list->Sort(list, compareFunction);

    int prev = list->Get(list, 0);
    printf("%d", prev);

    for (int i = 1; i < list->size; i++) {
        int temp = list->Get(list, i);
        if (temp != prev) {
            prev = temp;
            printf(", %d", prev);
        }
        
    }
    printf("\n");

    DeleteArrayList(list);
}