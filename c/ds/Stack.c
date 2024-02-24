#include "Stack.h"
#include "Util.h"

Stack* NewStack();
void DeleteStack(Stack* s);

static void Push(Stack*, void*);
static void* Peek(Stack*);
static void* Pop(Stack*);
static int IsEmpty(Stack*);
static int GetSize(Stack*);
static void PrintFromTopToBottom(Stack*);
static void PrintFromBottomToTop(Stack*);

Stack* NewStack() {
    Stack* s = malloc(sizeof(Stack));
    s->list = NewLinkedList();
    s->Push = Push;
    s->Peek = Peek;
    s->Pop = Pop;
    s->IsEmpty = IsEmpty;
    s->GetSize = GetSize;
    s->PrintFromBottomToTop = PrintFromBottomToTop;
    s->PrintFromTopToBottom = PrintFromTopToBottom;

    return s;
}

void DeleteStack(Stack* s) {
    DeleteLinkedList(s->list);
    free(s);
}

static void Push(Stack* s, void* v) {
    s->list->Append(s->list, v);
}

static void* Peek(Stack* s) {
    return s->list->tail->value;
}

static void* Pop(Stack* s) {
    void* ret = s->Peek(s);
    s->list->Delete(s->list, s->list->tail);
    return ret;
}

static int IsEmpty(Stack* s) {
    if (s->list->size == 0)
        return 1;
    else
        return 0;
}

static int GetSize(Stack* s) {
    return s->list->size;
}

static void PrintFromTopToBottom(Stack* s) {
    if (s->IsEmpty(s)) {
        return printf("empty\n");
    }

    LinkedListNode* tail = s->list->tail;

    printf("%d", tail->value);

    LinkedListNode* n = tail->prev;
    while (n != NULL) {
        printf(", %d", n->value);
        n = n->prev;
    }

    printf("\n");
}

static void PrintFromBottomToTop(Stack* s) {
    if (s->IsEmpty(s)) {
        return printf("empty\n");
    }

    LinkedListNode* head = s->list->head;

    printf("%d", head->value);

    LinkedListNode* n = head->next;
    while (n != NULL) {
        printf(", %d", n->value);
        n = n->next;
    }

    printf("\n");
}