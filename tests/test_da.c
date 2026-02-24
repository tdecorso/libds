#include <stdio.h>
#include <stdbool.h>

#include "ds/da.h"

#define TEST(fun)                   \
    do {                            \
        if ((fun)()) {              \
            printf(" FAILED\n");    \
            return 1;               \
        }                           \
        else printf(" SUCCESS\n");  \
    } while(0)

bool test_da_alloc() {
    printf("### Testing dynamic array allocation:");

    size_t elem_size = sizeof(int);
    size_t capacity = 5;

    da* arr = da_alloc(elem_size, capacity);

    if (!arr) return true;
    if (!arr->data) return true;
    if (arr->count != 0) return true;
    if (arr->capacity != capacity) return true;
    if (arr->element_size != elem_size) return true;

    da_free(arr);

    return false;
}

bool test_da_free() {
    printf("### Testing dynamic array deallocation:");

    da* arr = da_alloc(sizeof(int), 5);
    da_free(arr);
    arr = NULL;

    return false;
}

bool test_da_append() {
    printf("### Testing dynamic array appending:");

    da* arr = da_alloc(sizeof(int), 1);

    int values[3] = {1, 2, 3};

    da_append(arr, &values[0]);
    da_append(arr, &values[1]);
    da_append(arr, &values[2]);
    
    void* start = arr->data;
    void* end = arr->data + arr->count * arr->element_size;

    if (end - start != sizeof(int) * 3) return true;
    if (arr->count != 3) return true;
    if (arr->capacity != 4) return true;

    return false;
}

bool test_da_pop() {
    printf("### Testing dynamic array popping:");

    da* arr = da_alloc(sizeof(int), 5);

    int values[3] = {1, 2, 3};

    da_append(arr, &values[0]);
    da_append(arr, &values[1]);
    da_append(arr, &values[2]);
    
    int results[3] = {0};
    da_pop(arr, &results[0]);
    da_pop(arr, &results[1]);
    da_pop(arr, &results[2]);

    if (results[0] != 3) return true;
    if (results[1] != 2) return true;
    if (results[2] != 1) return true;

    return false;
}

int main(void) {
    TEST(test_da_alloc);
    TEST(test_da_free);
    TEST(test_da_append);
    TEST(test_da_pop);

    printf("### All tests passed.\n");
    return 0;
}
