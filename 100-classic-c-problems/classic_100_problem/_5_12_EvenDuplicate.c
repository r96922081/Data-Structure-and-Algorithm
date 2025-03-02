#include "Util.h"

static int compareFunction(const void* i, const void* j) {
    return (int)i - (int)j;
}

void _5_12_EvenDuplicate() {
    int a[] = {3, 4, 3, 2, 1, 3, 1, 1, 4, 3, 2, 2, 4, 2, 1, 4, 3, 4, 2, 1, 4, 3};
    int count = sizeof(a)/sizeof(int);
    int groupCount = log2(count);
    int groupElementCount = count / groupCount;

    LinkedList* all = NewLinkedList();

    int addedCount = 0;
    for (int i = 0; i < groupCount; i++) {
        ArrayList* l = NewArrayList();
        if (i < groupCount - 1) {
            for (int j = 0; j < groupElementCount; j++) {
                l->Append(l, a[addedCount]);
                addedCount++;
            }
        } else {
            while (addedCount < count) {
                l->Append(l, a[addedCount]);
                addedCount++;
            }
        }
        l->Sort(l, compareFunction);

        ArrayList* list2 = NewLinkedList();
        int value = -1;
        int count = 0;
        for (int j = 0; j < l->size; j++) {
            int newValue = l->Get(l, j);
            if (newValue == value)
                count++;
            else 
            {
                if (value != -1) {
                    Pair* p = malloc(sizeof(Pair));
                    p->first = value;
                    p->second = count;
                    list2->Append(list2, p);
                }

                value = newValue;
                count = 1;
            }
        }

        Pair* p = malloc(sizeof(Pair));
        p->first = value;
        p->second = count;
        list2->Append(list2, p);        
        all->Append(all, list2);
        DeleteArrayList(l);
    }

    while (all->size > 1) {
        for (int i = 0; i < all->size/2; i++) {
            LinkedListNode* n = all->head;
            for (int j = 0; j < i; j++)
                n = n->next;

            LinkedList* list1 = n->value;
            LinkedListNode* temp = n->next;
            all->Delete(all, n);
            n = temp;
            LinkedList* list2 = n->value;
            all->Delete(all, n);
            LinkedList* list3 = NewLinkedList();
            
            while (list1->size != 0 || list2->size != 0) {
                Pair* list1Pair = NULL;
                if (list1->size > 0)
                    list1Pair = list1->head->value;
                Pair* list2Pair = NULL;
                if (list2->size > 0)
                    list2Pair = list2->head->value; 
                
                if (list1Pair == NULL) {
                    list3->Append(list3, list2Pair);
                } else if (list2Pair == NULL) {
                    list3->Append(list3, list1Pair);
                } else {
                    if (list1Pair->first == list2Pair->first) {
                        list1Pair->second = (int)list1Pair->second + (int)list2Pair->second;
                        free(list2Pair);
                        list3->Append(list3, list1Pair);
                        list1->Delete(list1, list1->head);
                        list2->Delete(list2, list2->head);
                    } else if (list1Pair->first < list2Pair->first) {
                        list3->Append(list3, list1Pair);
                        list1->Delete(list1, list1->head);
                    } else {
                        list3->Append(list3, list2Pair);
                        list2->Delete(list2, list2->head);                        
                    }
                }
            }

            all->Append(all, list3);
            DeleteLinkedList(list1);
            DeleteLinkedList(list2);
        }
    }

    for (int i = 0; i < all->size; i++) {
        LinkedList* list = all->Get(all, i);
        printf("list %d\n", i);  
        for (LinkedListNode* n = list->head; n != NULL; n = n->next) {
            Pair* p = n->value;
            printf("%d(%d), ", p->first, p->second);
        }
        printf("\n");
    }

    for (int i = 0; i < all->size; i++) {
        LinkedList* list = all->Get(all, i);
        for (LinkedListNode* n = list->head; n != NULL; n = n->next) {
            free(n->value);
        }
        DeleteLinkedList(list);
    }

    DeleteLinkedList(all);
}