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


void _5_17_MaxVisitor() {
    ArrayList* list = NewArrayList();

    list->Append(list, NewPair(1, 4));
    list->Append(list, NewPair(2, 4));
    list->Append(list, NewPair(4, 7));
    list->Append(list, NewPair(5, 7));
    list->Append(list, NewPair(3, 8));
    ArrayList* list2 = NewArrayList();

    HashTable* t = NewHashTable();

    for (int i = 0; i < list->size; i++) {
        Pair* p = list->Get(list, i);
        int in = p->first;
        if (t->Contain(t, in)) {
            t->Put(t, in, (int)(t->Get(t, in)) + 1);
        } else {
            t->Put(t, in, 1);
        }

        int out = (int)p->second * -1;
        if (t->Contain(t, out)) {
            t->Put(t, out, (int)(t->Get(t, out)) + 1);
        } else {
            t->Put(t, out, 1);
        }        
    }

    for (LinkedListNode* n = t->keyList->head; n != NULL; n = n->next) {
        TableElement* e = n->value;
        int in = e->key >= 0 ? 1 : 0;
        list2->Append(list2, NewPair(in ? e->key: -e->key, in ? e->value : -(int)(e->value)));
    }


    list2->Sort(list2, sort);
    list2->Print2(list2, Print);

    int maxCount = 0;
    int maxStart = 0;
    int maxEnd = 0;
    int count = 0;

    for (int i = 0; i < list2->size; i++) {
        Pair* p = list2->Get(list2, i);
        
        if ((int)p->second >= 0) {          
            count += (int)p->second;  
            if (count >= maxCount) {
                maxCount = count;
                maxStart = p->first;
            }
        } else {
            if (count == maxCount) {
                maxEnd = p->first - 1;
            }
            count += (int)p->second;
        }
    }

    printf("Period: %d - %d, count = %d\n", maxStart, maxEnd, maxCount);

    DeleteHashTable(t);
    DeleteArrayListAndElement(list);
    DeleteArrayListAndElement(list2);
}