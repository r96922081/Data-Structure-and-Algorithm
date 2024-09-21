#include "Util.h"


void HashTableUt() {
    HashTable* table = NewHashTable();

    table->Put(table, 1, 11);
    table->Put(table, 2, 999);
    table->Put(table, 3, 0);
    check(table->Get(table, 1) == 11);
    table->Put(table, 1, 22);
    check(table->Get(table, 1) == 22);    
    table->Delete(table, 1);
    check(table->Get(table, 1) == NULL);    

    check(table->Get(table, 3) == NULL);
    check(table->Get(table, 4) == NULL);
    check(table->Contain(table, 3) == 1);
    check(table->Contain(table, 4) == 0);   

    table->keyList->Print(table->keyList); 

    DeleteHashTable(table);
}