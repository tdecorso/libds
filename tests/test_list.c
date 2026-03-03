#include "list.h"

#include <stdio.h>
#include <stdbool.h>

#define TEST(fun)                                              \
    do {                                                       \
        if ((fun)()) {printf("### Test failed.\n"); return 1;} \
    } while (0);                                               \

bool test_list_alloc() {
    printf("### Testing list alloc...\n");

    list_t* list = list_alloc();
    if (list->root) return true;
    if (list->tail) return true;
    if (list->count) return true;

    list_free(list);

    return false;
}

bool test_list_push_front() {
    printf("### Testing list push front...\n");

    list_t* list = list_alloc();

    int values[2] = {10, 20};

    list_push_front(list, &values[0]);

    if (!list->root) return true;
    if (!list->tail) return true;
    if (list->root != list->tail) return true;
    if (list->root->next != NULL) return true;
    if (list->root->prev != NULL) return true;
    if (*(int*)list->root->data != 10) return true;
    if (list->count != 1) return true;

    list_push_front(list, &values[1]);

    if (list->root->next != list->tail) return true;
    if (list->tail->prev != list->root) return true;
    if (list->tail->next) return true;
    if (*(int*)list->root->data != values[1]) return true;

    list_free(list);

    return false;
}

bool test_list_push_back() {
    printf("### Testing list push back...\n");

    list_t* list = list_alloc();

    int values[2] = {10, 20};

    list_push_back(list, &values[0]);

    if (!list->root) return true;
    if (!list->tail) return true;
    if (list->root != list->tail) return true;
    if (list->root->next != NULL) return true;
    if (list->root->prev != NULL) return true;
    if (*(int*)list->root->data != 10) return true;
    if (list->count != 1) return true;

    list_push_back(list, &values[1]);

    if (list->root->next != list->tail) return true;
    if (list->tail->prev != list->root) return true;
    if (list->tail->next) return true;
    if (*(int*)list->root->data != values[0]) return true;

    list_free(list);

    return false;
}

bool test_list_pop_front() {
    printf("### Testing list pop front...\n");

    list_t* list = list_alloc();

    int values[4] = {1, 2, 3, 4};

    list_push_back(list, &values[0]);

    if (!list->root) return true;
    if (!list->tail) return true;
    if (list->root != list->tail) return true;
    if (list->root->next != NULL) return true;
    if (list->root->prev != NULL) return true;
    if (*(int*)list->root->data != values[0]) return true;
    if (list->count != 1) return true;

    int* result = (int*) list_pop_front(list);

    if (list->root) return true;
    if (list->tail) return true;
    if (*result != values[0]) return true;
    if (list->count != 0) return true;

    list_push_back(list, &values[2]);
    list_push_back(list, &values[1]);
    list_push_back(list, &values[0]);

    result = (int*) list_pop_front(list);

    list_push_back(list, &values[3]);

    if (list->count != 3) return true;
    if (*result != values[2]) return true;
    if (list->root != list->root->next->prev) return true;
    if (list->tail->prev != list->root->next) return true;
    if (*(int*)list->tail->data != values[3]) return true;

    list_free(list);

    return false;
}

bool test_list_pop_back() {
    printf("### Testing list pop back...\n");

    list_t* list = list_alloc();

    int values[4] = {1, 2, 3, 4};

    list_push_back(list, &values[0]);

    if (!list->root) return true;
    if (!list->tail) return true;
    if (list->root != list->tail) return true;
    if (list->root->next != NULL) return true;
    if (list->root->prev != NULL) return true;
    if (*(int*)list->root->data != values[0]) return true;
    if (list->count != 1) return true;

    int* result = (int*) list_pop_back(list);

    if (list->root) return true;
    if (list->tail) return true;
    if (*result != values[0]) return true;
    if (list->count != 0) return true;

    list_push_back(list, &values[2]);
    list_push_back(list, &values[1]);
    list_push_back(list, &values[0]);

    result = (int*) list_pop_back(list);

    list_push_back(list, &values[3]);

    if (list->count != 3) return true;
    if (*result != values[0]) return true;
    if (list->root != list->root->next->prev) return true;
    if (list->tail->prev != list->root->next) return true;
    if (*(int*)list->tail->data != values[3]) return true;

    list_free(list);

    return false;
}

bool test_list_at() {
    printf("### Testing list at...\n");

    list_t* list = list_alloc();

    int values[3] = {1, 2, 3};
    list_push_front(list, &values[0]);
    list_push_front(list, &values[1]);
    list_push_front(list, &values[2]);

    lnode_t* second = list_at(list, 1);

    if (second->prev != list->root) return true;
    if (second->next != list->tail) return true;
    if (*(int*)second->data != values[1]) return true;

    list_free(list);

    return false;
}

bool test_list_remove_at() {
    printf("### Testing list remove at...\n");

    list_t* list = list_alloc();

    int values[3] = {1, 2, 3};
    list_push_front(list, &values[0]);
    list_push_front(list, &values[1]);
    list_push_front(list, &values[2]);

    void* result = list_remove_at(list, 1);

    if (list->count != 2) return true;
    if (list->root->next != list->tail) return true;
    if (list->tail->prev != list->root) return true;
    if (*(int*)result != values[1]) return true;

    list_free(list);

    return false;
}

int main(void) {

    printf("\n### Testing linked lists...\n\n");

    TEST(test_list_alloc);
    TEST(test_list_push_front);
    TEST(test_list_push_back);
    TEST(test_list_pop_front);
    TEST(test_list_pop_back);
    TEST(test_list_at);
    TEST(test_list_remove_at);

    printf("\n### All tests passed. Bye!\n\n");

    return 0;
}
