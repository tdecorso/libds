#include "ds/da.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

da* da_alloc(size_t element_size, size_t capacity)
{
    if (capacity == 0) capacity = 1;
    da* arr = malloc(sizeof(da));
    if(arr == NULL) {
        fprintf(stderr, "Error: could not allocate array.\n");
        exit(EXIT_FAILURE);
    }
    
    arr->data = malloc(element_size * capacity);
    arr->count = 0;
    arr->capacity = capacity;
    arr->element_size = element_size;

    if (arr->data == NULL) {
        fprintf(stderr, "Error: could not allocate array data.\n");
        exit(EXIT_FAILURE);
    }

    return arr;
}

void da_free(da* arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}

void da_append(da* arr, const void* element) {
    if (!arr) return;
    if (arr->capacity == 0) return;
    
    if (arr->count == arr->capacity) {
        void* tmp = realloc(arr->data, arr->capacity * 2);
        if (tmp == NULL) {
            fprintf(stderr, "Error: could not reallocate array data.\n");
            exit(EXIT_FAILURE);
        }
        arr->data = tmp;
        arr->capacity *= 2;
    }

    void* dest = arr->data + arr->count * arr->element_size;
    memcpy(dest, element, arr->element_size);
    arr->count++;
}

void da_pop(da* arr, void* element) {
    if (!arr) return;
    if (arr->count == 0) return;

    void* src = arr->data + (arr->count - 1) * arr->element_size;
    memcpy(element, src, arr->element_size);
    arr->count--;
}

void da_get(da* arr, size_t index, void* element) {
    if (!arr) return;
    if (arr->count == 0) return;

    void* src = arr->data + index * arr->element_size;
    memcpy(element, src, arr->element_size);
}

void da_set(da* arr, size_t index, const void* element) {
    if (!arr) return;
    
    if (arr->count < index + 1) {
        fprintf(stderr, "Error: no data to overwrite at given index.\n");
        exit(EXIT_FAILURE);
    }

    void* dest = arr->data + index * arr->element_size;
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
