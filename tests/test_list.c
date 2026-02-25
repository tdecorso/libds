#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ds/list.h"

#define TEST(fun)                   \
    do {                            \
        if ((fun)()) {              \
            printf("### Test failed.\n");  \
            return 1;               \
        }                           \
    } while(0)

bool test_node_alloc() {
    printf("### Testing node alloc...\n");

    node* n = node_alloc(sizeof(int));

    if (n == NULL) return true;
    if (n->data == NULL) return true;
    if (n->next != NULL) return true;
    if (n->prev != NULL) return true;

    node_free(n);

    return false;
}

bool test_node_free() {
    printf("### Testing node free...\n");

    node* n = node_alloc(sizeof(int));
    node_free(n);
    n = NULL;

    return false;
}

bool test_list_alloc() {
    printf("### Testing list alloc...\n");

    list* l = list_alloc(sizeof(int));

    if (l == NULL) return true;
    if (l->root != NULL) return true;
    if (l->tail != NULL) return true;
    if (l->count != 0) return true;
    if (l->element_size != sizeof(int)) return true;

    list_free(l);

    return false;
}

bool test_list_free() {
    printf("### Testing list free...\n");

    list* l = list_alloc(sizeof(double));
    list_free(l);
    l = NULL; 

    return false;
}

bool test_list_push_front() {
    printf("### Testing push front...\n");

    list* l = list_alloc(sizeof(int));

    int values[3] = {1, 2, 3};
    int results[3] = {0};

    list_push_front(l, &values[0]);
    list_push_front(l, &values[1]);
    list_push_front(l, &values[2]);

    node* second = l->root->next;
    node* third = l->tail;

    memcpy(&results[0], l->root->data, sizeof(int));
    memcpy(&results[1], second->data, sizeof(int));
    memcpy(&results[2], third->data, sizeof(int));
    
    if (l->root == NULL) return true;
    if (second == NULL) return true;
    if (second->prev != l->root) return true;
    if (third == NULL) return true;
    if (third->prev != second) return true;
    if (l->count != 3) return true;
    if (results[0] != 3) return true;
    if (results[1] != 2) return true;
    if (results[2] != 1) return true;

    list_free(l);

    return false;
}

bool test_list_push_back() {
    printf("### Testing push back...\n");

    list* l = list_alloc(sizeof(int));

    int values[3] = {1, 2, 3};
    int results[3] = {0};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    node* second = l->root->next;
    node* third = l->tail;

    memcpy(&results[0], l->root->data, sizeof(int));
    memcpy(&results[1], second->data, sizeof(int));
    memcpy(&results[2], third->data, sizeof(int));
    
    if (l->root == NULL) return true;
    if (second == NULL) return true;
    if (second->prev != l->root) return true;
    if (third == NULL) return true;
    if (third->prev != second) return true;
    if (l->count != 3) return true;
    if (results[0] != 1) return true;
    if (results[1] != 2) return true;
    if (results[2] != 3) return true;

    list_free(l);

    return false;
}

bool test_list_pop_front() {
    printf("### Testing pop front...\n");

    list* l = list_alloc(sizeof(int));

    int values[3] = {1, 2, 3};
    int results[3] = {0};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    list_pop_front(l, &results[0]); 
    list_pop_front(l, &results[1]); 
    list_pop_front(l, &results[2]); 

    if (l->root != NULL) return true;
    if (l->tail != NULL) return true;
    if (l->count != 0) return true;
    if (results[0] != 1) return true;
    if (results[1] != 2) return true;
    if (results[2] != 3) return true;

    list_free(l);

    return false;
}

bool test_list_pop_back() {
    printf("### Testing pop back...\n");

    list* l = list_alloc(sizeof(int));

    int values[3] = {1, 2, 3};
    int results[3] = {0};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    list_pop_back(l, &results[0]); 
    list_pop_back(l, &results[1]); 
    list_pop_back(l, &results[2]); 

    if (l->root != NULL) return true;
    if (l->count != 0) return true;
    if (results[0] != 3) return true;
    if (results[1] != 2) return true;
    if (results[2] != 1) return true;

    list_free(l);

    return false;
}

bool test_list_get() {
    printf("### Testing get...\n");

    list* l = list_alloc(sizeof(int));

    int values[3] = {1, 2, 3};
    int results[3] = {0};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    list_get(l, 0, &results[0]); 
    list_get(l, 1, &results[1]); 
    list_get(l, 2, &results[2]); 

    if (l->root == NULL) return true;
    if (l->count != 3) return true;
    if (results[0] != 1) return true;
    if (results[1] != 2) return true;
    if (results[2] != 3) return true;

    list_free(l);

    return false;
}

bool test_list_count() {
    printf("### Testing count...\n");

    list* l = list_alloc(sizeof(double));

    double values[3] = {1, 2, 3};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    if (l->root == NULL) return true;
    if (list_count(l) != 3) return true;

    list_free(l);

    return false;
}

bool test_list_node_at() {
    printf("### Testing node at...\n");

    list* l = list_alloc(sizeof(double));

    double values[3] = {1, 2, 3};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    node* first = list_node_at(l, 0);
    node* second = list_node_at(l, 1);
    node* third = list_node_at(l, 2);

    if (l->root == NULL) return true;
    
    if (!first || !second || !third) return true;
    if (first != l->root) return true;
    if (second != l->root->next) return true;
    if (third != ((node*)(l->root->next))->next) return true;

    list_free(l);

    return false;
}

bool test_list_remove_at() {
    printf("### Testing remove at...\n");

    list* l = list_alloc(sizeof(double));

    double values[3] = {1, 2, 3};
    double results[3] = {0};

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);

    list_remove_at(l, 1, &results[0]);

    if (results[0] != 2) return true;
    if (l->count != 2) return true;

    list_free(l);

    return false;
}

bool test_list_insert_at() {
    printf("### Testing insert at...\n");

    list* l = list_alloc(sizeof(double));

    double values[3] = {1, 2, 3};
    double results[6] = {0};

    list_push_front(l, &values[0]);
    list_push_front(l, &values[1]);
    list_push_front(l, &values[2]);

    list_insert_at(l, 0, &values[0]);
    list_insert_at(l, 1, &values[1]);
    list_insert_at(l, 2, &values[2]);

    list_get(l, 0, &results[0]);
    list_get(l, 1, &results[1]);
    list_get(l, 2, &results[2]);
    list_get(l, 3, &results[3]);
    list_get(l, 4, &results[4]);
    list_get(l, 5, &results[5]);

    if (results[0] != 1) return true;
    if (results[1] != 2) return true;
    if (results[2] != 3) return true;
    if (results[3] != 3) return true;
    if (results[4] != 2) return true;
    if (results[5] != 1) return true;
    if (l->count != 6) return true;

    list_free(l);

    return false;
}

int main(void) {

    printf("\n### Testing list module...\n###\n");

    TEST(test_node_alloc);
    TEST(test_node_free);
    TEST(test_list_alloc);
    TEST(test_list_free);
    TEST(test_list_push_front);
    TEST(test_list_push_back);
    TEST(test_list_pop_front);
    TEST(test_list_pop_back);
    TEST(test_list_get);
    TEST(test_list_count);
    TEST(test_list_node_at);
    TEST(test_list_remove_at);
    TEST(test_list_insert_at);

    printf("###\n### All tests passed. Bye! \n\n");

    return 0;
}
