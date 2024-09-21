#include "LinkedList.h"
#include "Util.h"

void LinkedListUt();
void LinkedListUt_Append_Get();
void LinkedListUt_InsertBefore();
void LinkedListUt_InsertAfter();
void LinkedListUt_Delete();

void LinkedListUt() {
    LinkedListUt_Append_Get();
    LinkedListUt_InsertBefore();
    LinkedListUt_InsertAfter();
    LinkedListUt_Delete();
}

void LinkedListUt_Append_Get() {
    LinkedList* list = NewLinkedList();
    list->Append(list, 1);
    list->Append(list, 2);
    list->Append(list, 3);

    check(list->Get(list, 0) == 1);
    check(list->Get(list, 1) == 2);
    check(list->Get(list, 2) == 3);
    check(list->size == 3);

    DeleteLinkedList(list);
}

void LinkedListUt_Delete() {
    LinkedList* list = NewLinkedList();
    list->Append(list, 1);
    list->Append(list, 2);
    list->Append(list, 3);

    list->Delete(list, list->head->next);
    check(list->head->next->value == 3);
    check(list->head->next->prev->value == 1);
    check(list->size == 2);

    list->Delete(list, list->head->next);
    check(list->tail == list->head);
    check(list->head->next == NULL);

    list->Delete(list, list->head);
    check(list->tail == list->head);
    check(list->head == NULL);
    check(list->size == 0);    

    DeleteLinkedList(list);
}

void LinkedListUt_InsertBefore() {
    LinkedList* list = NewLinkedList();

    list->Append(list, 1);

    list->head->InsertBefore(list->head, 0);
    check(list->size == 2);
    check(list->head->value == 0);
    check(list->head->next->value == 1);

    LinkedListNode* second = list->head->next;
    second->InsertBefore(second, -1);
    check(list->head->next->value == -1);

    DeleteLinkedList(list);
}

void LinkedListUt_InsertAfter() {
    LinkedList* list = NewLinkedList();
    list->Append(list, 1);

    list->head->InsertAfter(list->head, 2);
    check(list->size == 2);
    check(list->tail->value == 2);
    check(list->head->next->value == 2);

    LinkedListNode* second = list->head->next;
    second->InsertAfter(second, 3);
    check(second->next->value == 3);

    DeleteLinkedList(list);
}