#include "ds/list.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

node* node_alloc(size_t element_size) {
    assert(element_size != 0 && "Invalid element size");

    node* n = malloc(sizeof(node));
    assert(n != NULL && "Allocation failed");

    n->data = malloc(element_size);
    assert(n->data != NULL && "Allocation failed");

    n->next = NULL;
    n->prev = NULL;

    return n;
}

void node_free(node* n) {
    if (!n) return;
    
    free(n->data);

    n->next = NULL;
    n->prev = NULL;

    free(n);
}

list* list_alloc(size_t element_size) {
    assert(element_size != 0 && "Invalid element size");

    list* l = malloc(sizeof(list));
    assert(l != NULL && "Allocation failed");

    l->root = NULL;
    l->count = 0;
    l->element_size = element_size;

    return l;
}

void list_free(list* l) {
    if (l == NULL) return;
    
    if (l->count == 0) {
        free(l);
        return;
    }

    node* iter = l->root;

    while (iter != NULL) {
        node* next = iter->next;
        node_free(iter);
        iter = next;
    }

    free(l);
}

void list_push_front(list* l, const void* element) {
    assert(l != NULL && "Invalid list pointer");
    assert(element != NULL && "Invalid element pointer");

    node* new_root = node_alloc(l->element_size);
    assert(new_root != NULL && "Allocation failed");
    memcpy(new_root->data, element, l->element_size);

    if (l->root != NULL) {
        l->root->prev = new_root;
        new_root->next = l->root;
    }

    l->root = new_root;
    l->count++;
}

void list_push_back(list* l, const void* element) {
    assert(l != NULL && "Invalid list pointer");
    assert(element != NULL && "Invalid element pointer");

    node* new_tail = node_alloc(l->element_size);
    assert(new_tail != NULL && "Allocation failed");
    memcpy(new_tail->data, element, l->element_size);

    if (l->root == NULL) {
        l->root = new_tail;
        l->count++;
        return;
    }

    node* iter = l->root;
    while (iter->next != NULL) {
        iter = iter->next;
    }

    new_tail->prev = iter;
    iter->next = new_tail;
    l->count++;
}

void list_pop_front(list* l, void* element) {
    assert(l != NULL && "Invalid list pointer");
    assert(l->root != NULL && "Empty list");
    assert(element != NULL && "Invalid element pointer");

    memcpy(element, l->root->data, l->element_size);
    l->count--;

    node* tmp = l->root;
    l->root = l->root->next;
    if (l->root != NULL) l->root->prev = NULL;
    node_free(tmp);
}

void list_pop_back(list* l, void* element) {
    assert(l != NULL && "Invalid list pointer");
    assert(l->root != NULL && "Empty list");
    assert(element != NULL && "Invalid element pointer");

    node* iter = l->root;
    while (iter->next != NULL) {
        iter = iter->next;
    }

    memcpy(element, iter->data, l->element_size);
    node* prev = iter->prev;
    if (prev != NULL) {
        prev->next = NULL;
    }
    else {
        l->root = NULL;
    }

    node_free(iter);
    l->count--;
}

void list_get(list* l, size_t index, void* element) {
    assert(l != NULL && "Invalid list pointer");
    assert(l->count >= index + 1 && "Index out of bounds");

    node* iter = l->root;
    for (size_t i = 0; i < index; ++i) {
        iter = iter->next;
    }

    assert(iter->data != NULL && "Invalid data");
    memcpy(element, iter->data, l->element_size);
}

size_t list_count(list* l) {
    assert(l != NULL && "Invalid list pointer");
    return l->count;
}
