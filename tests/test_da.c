#include "tds.h"

#include <stdio.h>
#include <stdbool.h>

#define TEST(fun)                                              \
    do {                                                       \
        if ((fun)()) {printf("### Test failed.\n"); return 1;} \
    } while (0);                                               \


bool test_da_alloc() {

    printf("### Testing da_alloc...\n");

    size_t capacity = 10;
    int *numbers;
    da_alloc(numbers, capacity);

    if (numbers == NULL) return true;
    if (sizeof(numbers[0]) != sizeof(int)) return true;
    if (da_count(numbers) != 0) return true;
    if (da_capacity(numbers) != capacity) return true;

    da_free(numbers);

    return false;
}

bool test_da_push_back() {

    printf("### Testing da_push_back...\n");

    typedef struct {
        int some;
        float other;
    } item_t;

    item_t* items = NULL;

    for (int i = 0; i < 5; ++i){
        da_push_back(items, ((item_t){i, i+0.5f}));
    }

    if (!items) return true;
    if (da_count(items) != 5) return true;
    if (da_capacity(items) != 8) return true;

    for (int i = 0; i < 5; ++i) {
        if (items[i].some != i || items[i].other != i + 0.5f) return true;
    }

    da_free(items);

    return false;
}

int main(void) {

    printf("\n### Testing dynamic arrays...\n\n");

    TEST(test_da_alloc);
    TEST(test_da_push_back);

    printf("\n### All tests passed. Bye!\n\n");

    return 0;
}
