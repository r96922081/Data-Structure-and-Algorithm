#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Util.h"

typedef struct HashTable HashTable;

typedef struct HashTable {
    int _bucketCount;
    LinkedList** _table;
    void (*Put)(HashTable*, int, void*); // duplicate key overwrites old value of same key
    void* (*Get)(HashTable*, int);
    int (*Contain)(HashTable*, int); // eliminate unclear return value 0 & NULL of Get()
    void (*Delete)(HashTable*, int);
    LinkedList* keyList;
} HashTable;

typedef struct TableElement {
    LinkedListNode* _keyNode;
    int key;
    void* value;
} TableElement;

HashTable* NewHashTable();
void DeleteHashTable(HashTable*);
#endif