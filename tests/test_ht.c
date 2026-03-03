#include "ht.h"

#include <stdio.h>
#include <stdbool.h>

#define TEST(fun)                                              \
    do {                                                       \
        if ((fun)()) {printf("### Test failed.\n"); return 1;} \
    } while (0);                                               \

bool test_ht_alloc() {

    printf("### Testing ht alloc...\n");

    ht_t* table = ht_alloc(16, string_hash, string_equals);

    if (!table) return true;
    if (!table->hash) return true;
    if (!table->equals) return true;
    if (table->bucket_count != 16) return true;

    for (size_t i = 0; i < 16; ++i) {
        if (!table->buckets[i]) return true;
    }

    ht_free(table);

    return false;
}

bool test_ht_insert() {

    printf("### Testing ht insert...\n");

    ht_t* table = ht_alloc(16, string_hash, string_equals);

    char* key1 = "apple";
    int val1 = 42;
    ht_insert(table, key1, &val1);

    int* result = ht_get(table, key1);
    if (!result || *result != val1) return true;

    int val2 = 99;
    ht_insert(table, key1, &val2);

    result = ht_get(table, key1);
    if (!result || *result != val2) return true;

    ht_free(table);

    return false;
}

bool test_ht_remove() {

    printf("### Testing ht remove...\n");

    ht_t* table = ht_alloc(16, string_hash, string_equals);

    char* key1 = "apple";
    char* key2 = "banana";
    int val1 = 42;
    int val2 = 69;

    ht_insert(table, key1, &val1);
    ht_insert(table, key2, &val2);

    int* result = ht_get(table, key1);
    if (!result || *result != val1) return true;

    ht_insert(table, key2, &val2);

    result = ht_remove(table, key2);
    if (!result || *result != val2) return true;

    result = ht_get(table, key2);
    if (result) return true;

    ht_free(table);

    return false;
}

int main(void) {

    printf("\n### Testing hash tables...\n\n");

    TEST(test_ht_alloc);
    TEST(test_ht_insert);
    TEST(test_ht_remove);

    printf("\n### All tests passed. Bye!\n\n");

    return 0;
}
