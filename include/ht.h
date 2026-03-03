#ifndef H_TDS_HT
#define H_TDS_HT

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef size_t (*hash_fun)(const void*);
typedef bool (*equals_fun)(const void*, const void*);

typedef struct {
    void* key;
    void* value;
} htentry_t;

typedef struct {
    list_t** buckets;
    size_t bucket_count;
    hash_fun hash;
    equals_fun equals;
} ht_t;

static ht_t* ht_alloc(size_t bucket_count, hash_fun hash, equals_fun equals) {
    if (bucket_count == 0) bucket_count = 1;
    assert(hash && equals);
    ht_t* table = malloc(sizeof(ht_t));
    assert(table);
    table->equals = equals;
    table->hash = hash;
    table->bucket_count = bucket_count;
    table->buckets = malloc(sizeof(list_t*) * bucket_count);
    assert(table->buckets);
    for (size_t i = 0; i < bucket_count; ++i) {
        table->buckets[i] = list_alloc();
    }
    return table;
}

static void htentry_free(htentry_t* entry) {
    if (!entry) return;
    free(entry);
}

static void ht_free(ht_t* ht) {
    if (!ht) return;

    for (size_t i = 0; i < ht->bucket_count; ++i) {
        list_t* list = ht->buckets[i];
        lnode_t* iter = list->root;
        while (iter != NULL) {
            lnode_t* next = iter->next;
            htentry_free((htentry_t*) iter->data);
            iter = next;
        }
        list_free(ht->buckets[i]);
    }

    free(ht->buckets);
    free(ht);
}

static htentry_t* htentry_alloc() {
    htentry_t* entry = malloc(sizeof(htentry_t));
    assert(entry);
    return entry;
}

static void ht_insert(ht_t* ht, void* key, void* value) {
    assert(ht);
    assert(key && value);

    size_t index = ht->hash(key) % ht->bucket_count;
    list_t* bucket = ht->buckets[index];
    lnode_t* iter = bucket->root;

    while (iter != NULL) {
        htentry_t* entry = (htentry_t*)iter->data;

        if (ht->equals(key, entry->key)) {
            entry->key = key;
            entry->value = value;
            return;
        }

        iter = iter->next;
    }

    htentry_t* entry = htentry_alloc();
    entry->key = key;
    entry->value = value;

    list_push_back(bucket, entry);
}

static void* ht_get(ht_t* ht, void* key) {
    assert(ht);
    assert(key);

    size_t index = ht->hash(key) % ht->bucket_count;
    list_t* bucket = ht->buckets[index];
    
    lnode_t* iter = bucket->root;

    while (iter != NULL) {
        htentry_t* entry = (htentry_t*)iter->data;
        
        if (ht->equals(entry->key, key)) {
            return entry->value;
        }

        iter = iter->next;
    }

    return NULL;
}

static void* ht_remove(ht_t* ht, void* key) {
    assert(ht);
    assert(key);

    size_t index = ht->hash(key) % ht->bucket_count;
    list_t* bucket = ht->buckets[index];
    
    lnode_t* iter = bucket->root;

    size_t i = 0;
    while (iter != NULL) {
        htentry_t* entry = (htentry_t*)iter->data;
        if (ht->equals(entry->key, key)) {
            htentry_t* entry = list_remove_at(bucket, i);
            void* result = entry->value;
            htentry_free(entry);
            return result;
        }
        iter = iter->next;
        i++;
    }

    return NULL;
}

static size_t string_hash(const void *key) {
    const char* str = (const char*)key;
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static bool string_equals(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b) == 0;
}

#endif // H_TDS_HT
