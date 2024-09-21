#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedList LinkedList;

typedef struct LinkedList {
    int size;
    LinkedListNode* head;
    LinkedListNode* tail;
    void (*Append)(LinkedList*, void*);
    LinkedListNode* (*Get)(LinkedList*, int);
    void (*Delete)(LinkedList*, LinkedListNode*);
    void (*DeleteByValue)(LinkedList*, void*);
    void (*Print)(LinkedList*);
} LinkedList;

typedef struct LinkedListNode {
    LinkedListNode* next;
    LinkedListNode* prev;
    void* value;    
    void (*InsertAfter)(LinkedListNode*, void*);
    void (*InsertBefore)(LinkedListNode*, void*); 
    LinkedList* _list;
}LinkedListNode;

LinkedList* NewLinkedList();
void DeleteLinkedList(LinkedList*);

void LinkedListUt();

#endif