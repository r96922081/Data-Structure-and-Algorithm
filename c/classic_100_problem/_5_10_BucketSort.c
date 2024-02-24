#include "Util.h"

static ArrayList* BucketSort(ArrayList* a) {
    ArrayList* b = NewArrayList();

    LinkedList* bucketA[10] = {NULL};
    LinkedList* bucketB[10] = {NULL};

    for (int i = 0; i < 10; i++) {
        bucketA[i] = NewLinkedList();
        bucketB[i] = NewLinkedList();
    }

    LinkedList** bucket = bucketA;
    LinkedList** nextBucket = bucketB;
    for (int i = 0; i < a->size; i++)
        bucket[0]->Append(bucket[0], a->Get(a, i));

    for (int pow = 1;; pow *= 10) {
        int hasElement = 0;
        for (int i = 0; i < 10; i++) {
            LinkedList* c = bucket[i];
            for (LinkedListNode* n = c->head; n != NULL; ) {
                int value = n->value;
                if (value >= pow)
                    hasElement = 1;
                int nextPos = value % (pow * 10) / pow;
                nextBucket[nextPos]->Append(nextBucket[nextPos], value);
                LinkedListNode* temp = n->next;
                c->Delete(c, n);
                n = temp;
            }
        }
        if (bucket == bucketA) {
            bucket = bucketB;
            nextBucket = bucketA;
        } else {
            bucket = bucketA;
            nextBucket = bucketB;            
        }

        if (hasElement == 0)
            break;
    }

    for (int i = 0; i < 10; i++) {
        LinkedList* c = bucket[i];
        for (LinkedListNode* n = c->head; n != NULL; n = n->next) {
            b->Append(b, n->value);
        }
    }

    for (int i = 0; i < 10; i++) {
        DeleteLinkedList(bucketA[i]);
        DeleteLinkedList(bucketB[i]);
    }

    return b;
}

void _5_10_BucketSort() {
    srand(time(NULL));
    int n = 20;
    ArrayList* a = NewArrayList();

    a->Append(a, 9);
    for (int i = 0; i < n - 1; i++) {
        a->Append(a, rand() % 1000);
    }

    a->Print(a);
    
    ArrayList* b = BucketSort(a);

    b->Print(b);

    DeleteArrayList(a);   
    DeleteArrayList(b);     
}