#include "Queue.h"

Queue* NewQueue();
void DeleteQueue(Queue*);

static void Enqueue(Queue*, void*);
static void* Dequeue(Queue*);
static void* Peek(Queue*);
static int IsEmpty(Queue*);
static int GetSize(Queue*);

Queue* NewQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->Enqueue = Enqueue;
    q->Dequeue = Dequeue;
    q->Peek = Peek;
    q->IsEmpty = IsEmpty;
    q->GetSize = GetSize;
    q->list = NewLinkedList();

    return q;
}

void DeleteQueue(Queue* q) {
    DeleteLinkedList(q->list);
    free(q);
}

static void Enqueue(Queue* q, void* value)
{
    q->list->Append(q->list, value);
}

static void* Dequeue(Queue* q)
{
    void* ret = q->list->head->value;
    q->list->Delete(q->list, q->list->head);
    return ret;
}

static void* Peek(Queue* q)
{
    return q->list->head->value;
}

static int IsEmpty(Queue* q)
{
    return q->list->size == 0;
}

static int GetSize(Queue* q)
{
    return q->list->size;
}