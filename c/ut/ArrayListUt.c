#include "ArrayList.h"

void ArrayListUt();

static void Get_Set_Append();
static void Sort();
static int compareFunction(const void*, const void*);
static void Delete();


void ArrayListUt() {
    Get_Set_Append();
    Sort();
    Delete();
}

static void Delete() {
    ArrayList* l = NewArrayList();

    for (int i = 0; i < 5; i++) 
        l->Append(l, i);
    
    l->Delete(l, 2);
    check(l->Get(l, 3) == 4);
    check(l->Get(l, 2) == 3);
    check(l->Get(l, 1) == 1);
    l->Delete(l, 3);
    l->Delete(l, 0);
    l->Delete(l, 1);
    l->Delete(l, 0);

    check(l->size == 0);
    check(l->capacity == 0);

    for (int i = 0; i < 10; i++) {
        l->Append(l, i);
    }
    check(l->size == 10);
    check(l->Get(l, 9) == 9);

    DeleteArrayList(l);
}

static int compareFunction(const void* i, const void* j) {
    return (int)i - (int)j;
}


static void Get_Set_Append() {
    ArrayList* l = NewArrayList();

    for (int i = 0; i < 100; i++) {
        l->Append(l, i);
    }

    check(l->size == 100);
    for (int i = 0; i < 100; i++) {
        check(l->Get(l, i) == i);
    }  

    l->Set(l, 1, 111);
    check(l->Get(l, 1) == 111);

    DeleteArrayList(l);
}

static void Sort() {
    ArrayList* l = NewArrayList();

    for (int i = 0; i < 100; i++) {
        l->Append(l, 99 - i);
    }

    l->Sort(l, compareFunction);

    for (int i = 0; i < 100; i++) {
        check(l->Get(l, i) == i);
    }

    DeleteArrayList(l);
}