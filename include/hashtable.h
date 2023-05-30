#ifndef __UIENGINE_HASHTABLE_H__
#define __UIENGINE_HASHTABLE_H__

#include <stdint.h>
#include "dlist.h"

typedef DListNode (*HashTableInsert)(struct HashTable*, void *, void *);
typedef DListNode (*HashTableRemove)(struct HashTable*, void *);
typedef DListNode (*HashTableSearch)(struct HashTable*, void *);
typedef struct HashTable {
    DListNode *slots;

    HashTableInsert insert;
    HashTableRemove remove;
    HashTableSearch search;
} HashTable;

HashTable *hashtable_create(uint32_t slot);

#endif /* __UIENGINE_HASHTABLE_H__ */