#include <stdio.h>
#include <stdbool.h>

#include "tds/stack.h"

#define TEST(fun)                   \
    do {                            \
        if ((fun)()) {              \
            printf("### Test failed.\n");  \
            return 1;               \
        }                           \
    } while(0)

bool test_stack_alloc() {
    printf("### Testing alloc...\n");

    stack* s = stack_alloc(sizeof(double), 5);
    
    if (s == NULL) return true;
    if (s->arr == NULL) return true;

    stack_free(s);
    
    return false;
}

bool test_stack_free() {
    printf("### Testing free...\n");

    stack* s = stack_alloc(sizeof(int), 5);
    stack_free(s);
    s = NULL;
    
    return false;
}

bool test_stack_push() {
    printf("### Testing push...\n");

    stack* s = stack_alloc(sizeof(int), 5);
    int value = 4;
    stack_push(s, &value);
    
    int result = 0;
    da_get(s->arr, 0, &result);
    if (result != 4) return true;

    stack_free(s);
    
    return false;
}

bool test_stack_pop() {
    printf("### Testing pop...\n");

    stack* s = stack_alloc(sizeof(int), 5);

    int values[3] = {1, 2, 3};
    stack_push(s, &values[0]);
    stack_push(s, &values[1]);
    stack_push(s, &values[2]);
    
    int results[3] = {0};
    stack_pop(s, &results[0]);
    stack_pop(s, &results[1]);
    stack_pop(s, &results[2]);

    if (results[0] != 3) return true;
    if (results[1] != 2) return true;
    if (results[2] != 1) return true;

    stack_free(s);
    
    return false;
}

bool test_stack_peek() {
    printf("### Testing peek...\n");

    stack* s = stack_alloc(sizeof(double), 5);

    double values[3] = {1, 2, 3};
    stack_push(s, &values[0]);
    stack_push(s, &values[1]);
    stack_push(s, &values[2]);
    
    double results[3] = {0};
    stack_peek(s, &results[0]);
    stack_peek(s, &results[1]);
    stack_peek(s, &results[2]);

    if (results[0] != 3) return true;
    if (results[1] != 3) return true;
    if (results[2] != 3) return true;

    stack_free(s);
    
    return false;
}

bool test_stack_count() {
    printf("### Testing count...\n");

    stack* s = stack_alloc(sizeof(int), 5);

    int values[3] = {1, 2, 3};
    stack_push(s, &values[0]);
    stack_push(s, &values[1]);
    stack_push(s, &values[2]);
    
    if (stack_count(s) != 3) return true;

    stack_free(s);
    
    return false;
}

bool test_stack_is_empty() {
    printf("### Testing is_empty...\n");

    stack* s = stack_alloc(sizeof(int), 5);

    if (!stack_is_empty(s)) return true;

    int value = 1;
    stack_push(s, &value);

    if (stack_is_empty(s)) return true;

    stack_free(s);
    
    return false;
}

int main(void) {

    printf("\n### Testing stack module...\n###\n");

    TEST(test_stack_alloc);
    TEST(test_stack_free);
    TEST(test_stack_push);
    TEST(test_stack_pop);
    TEST(test_stack_peek);
    TEST(test_stack_count);
    TEST(test_stack_is_empty);

    printf("###\n### All tests passed. Bye! \n\n");

    return 0;
}
