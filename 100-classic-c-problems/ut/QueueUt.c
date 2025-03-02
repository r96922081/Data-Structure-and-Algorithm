#include "Util.h"

void QueueUt()
{
    Queue* q = NewQueue();
    check(q->GetSize(q) == 0);

    q->Enqueue(q, 0);
    q->Enqueue(q, 1);
    q->Enqueue(q, 2);

    check(q->Dequeue(q) == 0);
    check(q->Peek(q) == 1);
    check(q->GetSize(q) == 2);
    check(q->Dequeue(q) == 1);
    check(q->Dequeue(q) == 2);

    check(q->IsEmpty(q));

    DeleteQueue(q);
}