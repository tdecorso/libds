#include "ds/da.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

da* da_alloc(size_t element_size, size_t capacity)
{
    if (capacity == 0) capacity = 1;
    da* arr = malloc(sizeof(da));

    assert(arr != NULL && "Allocation failed");
    
    arr->data = malloc(element_size * capacity);
    arr->count = 0;
    arr->capacity = capacity;
    arr->element_size = element_size;

    assert(arr->data != NULL && "Allocation failed");

    return arr;
}

void da_free(da* arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}

void da_append(da* arr, const void* element) {
    assert(arr != NULL && "Array pointer is null");

    if (arr->count == arr->capacity) {
        void* tmp = realloc(arr->data, arr->capacity * arr->element_size * 2);

        assert(tmp != NULL && "Allocation failed");

        arr->data = tmp;
        arr->capacity *= 2;
    }

    char* dest = (char*) arr->data + arr->count * arr->element_size;
    memcpy(dest, element, arr->element_size);
    arr->count++;
}

void da_pop(da* arr, void* element) {
    assert(arr != NULL && "Array pointer is null");
    assert(arr->count != 0 && "Array is empty");

    char* src = (char*) arr->data + (arr->count - 1) * arr->element_size;
    memcpy(element, src, arr->element_size);
    arr->count--;
}

void da_get(da* arr, size_t index, void* element) {
    assert(arr != NULL && "Array pointer is null");
    assert(arr->count >= index + 1 && "Given index invalid");

    char* src = (char*) arr->data + index * arr->element_size;
    memcpy(element, src, arr->element_size);
}

void da_set(da* arr, size_t index, const void* element) {
    assert(arr != NULL && "Array pointer is null");
    assert(arr->count >= index + 1 && "Given index invalid");

    char* dest = (char*) arr->data + index * arr->element_size;
    memcpy(dest, element, arr->element_size);
}

size_t da_count(const da* arr) {
    if (!arr) return 0;
    return arr->count;
}

size_t da_capacity(const da* arr) {
    if (!arr) return 0;
    return arr->capacity;
}
