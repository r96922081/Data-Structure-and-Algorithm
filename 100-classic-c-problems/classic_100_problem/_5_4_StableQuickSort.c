#include "Util.h"
#include "time.h"
#include "LinkedList.h"

static void Pivot(LinkedList* list, Triple* ret) {
    int value = list->head->value;

    ret->second = value;

    for (LinkedListNode* n = list->head->next; n != NULL; n = n->next) {
        if (n->value < value) {
            if (ret->first == NULL)
                ret->first = NewLinkedList();
            LinkedList* less = ret->first;
            less->Append(less, n->value);
        } else {
            if (ret->third == NULL)
                ret->third = NewLinkedList();
            LinkedList* equalAndGreater = ret->third;
            equalAndGreater->Append(equalAndGreater, n->value);            
        }
    }
}

static LinkedList* StableQuickSort(LinkedList* src) {
    if (src == NULL)
        return NULL;

    Triple t;
    memset(&t, 0, sizeof(Triple));

    Pivot(src, &t);
    LinkedList* less = t.first;
    LinkedList* less2 = NULL;
    if (less != NULL) {
        less2 = StableQuickSort(less);
        DeleteLinkedList(less);
    }

    int value = t.second;

    LinkedList* equalOrGreater = t.third;
    LinkedList* equalOrGreater2 = NULL;
    if (equalOrGreater != NULL) {
        equalOrGreater2 = StableQuickSort(equalOrGreater);
        DeleteLinkedList(equalOrGreater);
    }

    LinkedList* ret = NewLinkedList();
    if (less2 != NULL) {
        for (LinkedListNode* n = less2->head; n != NULL; n = n->next) {
            ret->Append(ret, n->value);
        }
        DeleteLinkedList(less2);
    }

    ret->Append(ret, value);

    if (equalOrGreater2 != NULL) {
        for (LinkedListNode* n = equalOrGreater2->head; n != NULL; n = n->next) {
            ret->Append(ret, n->value);
        }
        DeleteLinkedList(equalOrGreater2);
    }    
    
    return ret;
}

void _5_4_StableQuickSort() {
    srand(time(NULL));

    int count = 20;
    LinkedList* src = NewLinkedList();

    for (int i = 0; i < count; i++) {
        src->Append(src, rand() % 100 + 1);
    }

    src->Print(src);
    
    LinkedList* result = StableQuickSort(src);

    result->Print(result);

    DeleteLinkedList(src);
    DeleteLinkedList(result);
}
