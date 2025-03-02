#include "Stack.h"

void StackUt() {
    Stack* s = NewStack();

    check(s->IsEmpty(s) == 1);
    s->Push(s, 0);
    s->Push(s, 1);
    s->Push(s, 2);
    check(s->IsEmpty(s) == 0);
    check(s->Peek(s) == 2);
    s->Pop(s);
    s->Pop(s);
    check(s->Pop(s) == 0);
    check(s->IsEmpty(s) == 1);

    DeleteStack(s);
}