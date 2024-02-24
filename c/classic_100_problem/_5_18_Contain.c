#include "Util.h"

static int sort(void* a, void* b) {
    Pair* p1 = a;
    Pair* p2 = b;

    if (p1->first < p2->first)
        return -1;
    else if (p1->first == p2->first) {
        if (p1->second == p2->second)
            return 0;
        else if (p2->second < p1->second)
            return -1;
        else
            return 1;
    } else {
        return 1;
    }
}

static void Print(void* v) {
    Pair* p = v;
    printf("(%d, %d)", p->first, p->second);
}


void _5_18_Contain() {
    ArrayList* list = NewArrayList();

    list->Append(list, NewPair(1, 4));
    list->Append(list, NewPair(1, 4));
    list->Append(list, NewPair(2, 4));
    list->Append(list, NewPair(4, 9));
    list->Append(list, NewPair(4, 7));
    list->Append(list, NewPair(5, 7));
    list->Append(list, NewPair(3, 8));
    list->Append(list, NewPair(4, 8));

    list->Sort(list, sort);
    list->Print2(list, Print);

    for (int i = 0; i < list->size; i++) {
        int hit = 0;
        Pair* segment1 = list->Get(list, i);
        for (int j = i - 1; j >= 0; j--) {
            Pair* segment2 = list->Get(list, j);
            if (segment2->second >= segment1->second) {
                if (hit == 0) {
                    hit = 1;
                    printf("(%d, %d) is contained by: ", segment1->first, segment1->second);
                    printf("(%d, %d)", segment2->first, segment2->second);
                } else {
                    printf(", (%d, %d)", segment2->first, segment2->second);
                }
            }
        }

        if (hit)
            printf("\n");
    }

    DeleteArrayListAndElement(list);
}