#include "ArrayList.h"
#include "Util.h"

typedef struct ArrayList ArrayList;

ArrayList* NewArrayList();
ArrayList* NewArrayList2(int size);
void DeleteArrayList(ArrayList* list) ;
void DeleteArrayListAndElement(ArrayList* list) ;

static void Append(ArrayList* list, void* value);
static void* Get(ArrayList* list, int index);
static void Set(ArrayList* list, int index, void* value);
static void Delete(ArrayList* list, int index);
static void Sort(ArrayList* list, int (*compareFunction)(const void *, const void*));
static void Sort2(ArrayList* list, int low, int high, int (*compareFunction)(const void *, const void*));
static int SortPartition(ArrayList* list, int low, int high, int (*compareFunction)(const void *, const void*));
static void SortSwap(ArrayList* list, int i, int j);
static void Print(ArrayList* this);
static void Print2(ArrayList* this, void (*printFunction)(const void*)) ;


ArrayList* NewArrayList() {
    return NewArrayList2(0);
}

ArrayList* NewArrayList2(int size) {
    ArrayList* list = calloc(1, sizeof(ArrayList));
    list->capacity = size;
    list->size = size;
    if (size != 0)
        list->data = calloc(sizeof(void*), size);
    list->Get = Get;
    list->Append = Append;
    list->Set = Set;
    list->Delete = Delete;
    list->Sort = Sort;
    list->Print = Print;
    list->Print2 = Print2;

    return list;    
}

void DeleteArrayList(ArrayList* list) {
    if (list->data != NULL)
        free(list->data);
    free(list);
}

void DeleteArrayListAndElement(ArrayList* list) {
    for (int i = 0; i < list->size; i++)
        free(*(list->data + i));
    DeleteArrayList(list);
}

static void Print(ArrayList* this) {
    if (this->size != 0) {
        printf("%d", this->Get(this, 0));
        for (int i = 1; i < this->size; i++)
        {
            printf(", %d", this->Get(this, i));
        }
    }

    printf("\n");
}


static void Print2(ArrayList* this, void (*printFunction)(const void*)) {
    if (this->size != 0) {
        printFunction(this->Get(this, 0));
        for (int i = 1; i < this->size; i++)
        {
            printf(", ");
            printFunction(this->Get(this, i));
        }
    }

    printf("\n");
}

static void Append(ArrayList* list, void* value) {
    if (list->capacity == 0) {
        list->capacity = 1;
        list->data = calloc(1, sizeof(void*));    
    }

    if (list->size + 1 > list->capacity) {
        list->capacity *= 2;
        void** data2 = malloc(list->capacity * sizeof(void*));
        memcpy(data2, list->data, sizeof(void*) * list->capacity/2);
        free(list->data);
        list->data = data2;
    }

    void** dest = (list->data + list->size);
    *dest = value;
    list->size++;
}

static void* Get(ArrayList* list, int index) {
    return *(list->data + index);
}

static void Set(ArrayList* list, int index, void* value) {
    *(list->data + index) = value;
}

static void Delete(ArrayList* list, int index) {
    ArrayList* left = NULL;
    ArrayList* right = NULL;
    if (index != 0) {
        int count = index;
        left = NewArrayList2(count);
        memcpy(left->data, list->data, sizeof(void*) * count);
        left->size = count;
        left->capacity = count;
    }

    if (index != list->size - 1) {
        int count = list->size -1 - index;
        right = NewArrayList2(count);
        memcpy(right->data, list->data + (index + 1), sizeof(void*) * count);
        right->size = count;
        right->capacity = count;
    }

    free(list->data);
    list->size--;
    list->capacity = list->size;
    if (list->size == 0)
        list->data = NULL;
    else
        list->data = calloc(sizeof(void*), list->size);

    if (left != NULL) {
        memcpy(list->data, left->data, sizeof(void*) * left->size);
        DeleteArrayList(left);  
    }
    if (right != NULL) {
        memcpy(list->data + index, right->data, sizeof(void*) * right->size);
        DeleteArrayList(right);  
    }  
}

static void SortSwap(ArrayList* list, int i, int j) {
    void* temp = list->Get(list, j);
    void* iValue = list->Get(list, i);
    list->Set(list, j, iValue);
    list->Set(list, i, temp);
}


static int SortPartition(ArrayList* list, int low, int high, int (*compareFunction)(const void *, const void*)) {
    int pivot = list->Get(list, high);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        int jValue = list->Get(list, j);
        if (compareFunction(jValue, pivot) <= 0) {
            i++;
            SortSwap(list, i, j);
        }
    }
    SortSwap(list, i + 1, high);
    return (i + 1);
}

static void Sort2(ArrayList* list, int low, int high, int (*compareFunction)(const void *, const void*)) {
    if (low < high) {
        int pivot = SortPartition(list, low, high, compareFunction);
        Sort2(list, low, pivot - 1, compareFunction);
        Sort2(list, pivot + 1, high, compareFunction);  
    }
}

static void Sort(ArrayList* list, int (*compareFunction)(const void *, const void*)) {
    Sort2(list, 0, list->size - 1, compareFunction);
}