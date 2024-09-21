#include "Util.h"

typedef struct HashTable HashTable;
HashTable* NewHashTable();
void DeleteHashTable(HashTable*);
static void Put(HashTable*, int, void*);
static void* Get(HashTable*, int);
static int Contain(HashTable*, int);
static void Delete(HashTable*, int);
static int GetBucket(int);


// key = 123456, p = 14, ω = 32, h(k) = 14 MSB of ((123456 * 2,654,435,769) % 2^32) = 14 MSB of 17612864 = 67
static int GetBucket(int key) {
    // 17612864
    unsigned int v = (unsigned int)((((long long)key) * ((long long)2654435769)) & (unsigned int)0xffffffff);

    // 14 MSB of 17612864
    return v >> (32 - 14);
}


HashTable* NewHashTable() {
    HashTable* ht = malloc(sizeof(HashTable));
    int bucketCount = 1024 * 16;
    ht->_bucketCount = bucketCount;
    ht->_table = calloc(bucketCount, sizeof(LinkedList*));
    for (int i = 0; i < bucketCount; i++)
        ht->_table[i] = NewLinkedList();
    ht->Get = Get;
    ht->Delete = Delete;
    ht->Put = Put;
    ht->Contain = Contain;
    ht->keyList = NewLinkedList();
    return ht;
}

void DeleteHashTable(HashTable* ht) {
    for (int i = 0; i < ht->_bucketCount; i++) {
        LinkedList* list = ht->_table[i];
        for (LinkedListNode* n = list->head; n != NULL; n = n->next)
            free(n->value);
        DeleteLinkedList(list);
    }
    DeleteLinkedList(ht->keyList);
    free(ht->_table);
    free(ht);
}

static void Put(HashTable* ht, int key, void* value) {
    LinkedList* bucket = ht->_table[GetBucket(key) - 1];
    for (LinkedListNode* n = bucket->head; n != NULL; n = n->next) {
        TableElement* e = n->value;
        if (e->key == key) {
            e->value = value;
            e->_keyNode->value = e;
            return;
        }
    }
    TableElement* e = malloc(sizeof(TableElement));
    e->key = key;
    e->value = value;
    ht->keyList->Append(ht->keyList, e);    
    e->_keyNode = ht->keyList->tail;
    bucket->Append(bucket, e);
}

static void* Get(HashTable* ht, int key) {
    LinkedList* bucket = ht->_table[GetBucket(key) - 1];
    for (LinkedListNode* n = bucket->head; n != NULL; n = n->next) {
        TableElement* e = n->value;
        if (e->key == key) {
            return e->value;
        }
    }

    return NULL;
}

static int Contain(HashTable* ht, int key) {
    LinkedList* bucket = ht->_table[GetBucket(key) - 1];
    for (LinkedListNode* n = bucket->head; n != NULL; n = n->next) {
        TableElement* e = n->value;
        if (e->key == key) {
            return 1;
        }
    }

    return 0;
}

static void Delete(HashTable* ht, int key) {
    LinkedList* bucket = ht->_table[GetBucket(key) - 1];
    for (LinkedListNode* n = bucket->head; n != NULL; n = n->next) {
        TableElement* e = n->value;
        if (e->key == key) {
            ht->keyList->Delete(ht->keyList, e->_keyNode);
            free(n->value);
            bucket->Delete(bucket, n);
            break;
        }
    }
}