#ifndef H_DA
#define H_DA

#include <stdlib.h>

typedef struct {
    void* data;
    size_t count;
    size_t capacity;
    size_t element_size;
} da;

// Allocates a new array on the heap
da* da_alloc(size_t element_size, size_t capacity);

// Frees the array
void da_free(da* arr);

// Appends an element to the back of the array
void da_append(da* arr, const void* element);

// Pops last element from the array
void da_pop(da* arr, void* element);

#endif // H_DA
