#include "LinkedList.h"
#include "Util.h"

LinkedList* NewLinkedList();
void DeleteLinkedList(LinkedList*);

static void Append(LinkedList* this, void* value);
static void Delete(LinkedList*, LinkedListNode*);
static void DeleteByValue(LinkedList*, void*);
static void* Get(LinkedList* this, int index);
static void Print(LinkedList*);

LinkedListNode* NewLinkedListNode(LinkedList* list, void* value);
static void InsertAfter(LinkedListNode* this, void* value);    
static void InsertBefore(LinkedListNode* this, void* value);

LinkedListNode* NewLinkedListNode(LinkedList* list, void* value) {
    LinkedListNode* n = calloc(1, sizeof(LinkedListNode));
    n->InsertAfter = InsertAfter;
    n->InsertBefore = InsertBefore;
    n->value = value;
    n->_list = list;

    return n;
}

static void InsertAfter(LinkedListNode* this, void* value) {
    LinkedListNode* n = NewLinkedListNode(this->_list, value);

    if (this == this->_list->tail) {
        this->next = n;
        n->prev = this;
        this->_list->tail = n;
    } else {
        n->next = this->next;
        n->prev = this;
        this->next->prev = n;
        this->next = n;
    }

    this->_list->size++;
}
    
static void InsertBefore(LinkedListNode* this, void* value) {
    LinkedListNode* n = NewLinkedListNode(this->_list, value);

    if (this == this->_list->head) {
        this->prev = n;
        n->next = this;
        this->_list->head = n;
    } else {
        n->prev = this->next;
        n->next = this;
        this->prev->next = n;
        this->prev = n;
    }

    this->_list->size++;
}

static void Delete(LinkedList* list, LinkedListNode* n) {
    if (n == list->head && list->size == 1) {
        list->head = list->tail = NULL;      
    } else if (n == list->head) {
        n->next->prev = NULL;
        list->head = n->next;          
    } else if (n == list->tail) {
        n->prev->next = NULL;
        list->tail = n->prev;          
    } else {
        n->next->prev = n->prev;
        n->prev->next = n->next;
    }

    list->size--;
    
    free(n);
}

static void DeleteByValue(LinkedList* list, void* value) {
    for (LinkedListNode* n = list->head; n != NULL;) {
        LinkedListNode* next = n->next;
        if (n->value == value) {
            list->Delete(list, n);
        }
        n = next;
    }
}

static void Append(LinkedList* this, void* value) {
    LinkedListNode* n = NewLinkedListNode(this, value);

    if (this->head == NULL) {
        this->head = this->tail = n;
    } else {
        this->tail->next = n;
        n->prev = this->tail;
        this->tail = n;
    }

    this->size++;
}

static void* Get(LinkedList* this, int index) {
    if (this->size <= index) {
        return NULL;
    }

    LinkedListNode* n = this->head;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }

    return n->value;
}

static void Print(LinkedList* this) {
    if (this->head == NULL)
        return;

    printf("%d", this->head->value);

    LinkedListNode* next = this->head->next;
    while (next) {
        printf(", %d", next->value);
        next = next->next;
    }

    printf("\n");
}


LinkedList* NewLinkedList() {
    LinkedList* l = calloc(1, sizeof(LinkedList));
    l->Append = Append;
    l->Get = Get;
    l->Delete = Delete;
    l->DeleteByValue = DeleteByValue;
    l->Print = Print;
    return l;
}

void DeleteLinkedList(LinkedList* l) {
    LinkedListNode* node = l->head;
    while (node != NULL) {
        LinkedListNode* temp = node->next;
        free(node);
        node = temp;
    }
    free(l);
}