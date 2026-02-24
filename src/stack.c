#include "ds/stack.h"

#include <assert.h>

stack* stack_alloc(size_t element_size, size_t capacity) {
    if (capacity == 0) capacity = 1;

    stack* s = malloc(sizeof(stack));
    assert(s != NULL && "Allocation failed");
    
    s->arr = da_alloc(element_size, capacity);
    assert(s->arr != NULL && "Allocation failed");

    return s;
}

void stack_free(stack* s) {
    if (!s) return;
    da_free(s->arr);
    free(s);
}

void stack_push(stack* s, const void* element) {
    assert(s != NULL && "Invalid stack pointer"); 
    assert(element != NULL && "Invalid element pointer"); 
    assert(s->arr != NULL && "Invalid stack array");

    da_append(s->arr, element);
}

void stack_pop(stack* s, void* element) {
    assert(s != NULL && "Invalid stack pointer"); 
    assert(element != NULL && "Invalid element pointer"); 
    assert(s->arr != NULL && "Invalid stack array");
    assert(da_count(s->arr) != 0 && "Empty stack");

    da_pop(s->arr, element);
}

void stack_peek(stack* s, void* element) {
    assert(s != NULL && "Invalid stack pointer"); 
    assert(element != NULL && "Invalid element pointer"); 
    assert(s->arr != NULL && "Invalid stack array");
    assert(da_count(s->arr) != 0 && "Empty stack");

    da_get(s->arr, da_count(s->arr) - 1, element);
}

size_t stack_count(stack* s) {
    assert(s != NULL && "Invalid stack pointer"); 
    assert(s->arr != NULL && "Invalid stack array");

    return da_count(s->arr);
}

bool stack_is_empty(stack* s) {
    assert(s != NULL && "Invalid stack pointer"); 
    assert(s->arr != NULL && "Invalid stack array");

    return stack_count(s) == 0;
}
