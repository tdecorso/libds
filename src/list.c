#include "ds/list.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

node* node_alloc(size_t element_size) {
    assert(element_size != 0);

    node* n = malloc(sizeof(node));
    assert(n != NULL);

    n->data = malloc(element_size);
    assert(n->data != NULL);

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
    assert(element_size != 0);

    list* l = malloc(sizeof(list));
    assert(l != NULL);

    l->root = NULL;
    l->tail = NULL;
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
    assert(l != NULL);
    assert(element != NULL);

    node* new_root = node_alloc(l->element_size);
    assert(new_root != NULL);
    memcpy(new_root->data, element, l->element_size);

    if (l->root == NULL) {
        l->root = new_root;
        l->tail = new_root;
        l->count++;
        return;
    }

    new_root->next = l->root;
    l->root->prev = new_root;
    l->root = new_root;
    l->count++;
}

void list_push_back(list* l, const void* element) {
    assert(l != NULL);
    assert(element != NULL);

    node* new_tail = node_alloc(l->element_size);
    assert(new_tail != NULL);
    memcpy(new_tail->data, element, l->element_size);

    if (l->tail == NULL) {
        l->tail = new_tail;
        l->root = l->tail;
        l->count++;
        return;
    }

    l->tail->next = new_tail;
    new_tail->prev = l->tail;
    l->tail = new_tail;
    l->count++;
}

void list_pop_front(list* l, void* element) {
    assert(l != NULL);
    assert(l->root != NULL);
    assert(element != NULL);

    memcpy(element, l->root->data, l->element_size);
    l->count--;

    node* tmp = l->root;
    if (l->root->next == NULL) {
        l->tail = NULL;
    }
    l->root = l->root->next;
    if (l->root != NULL) l->root->prev = NULL;
    node_free(tmp);
}

void list_pop_back(list* l, void* element) {
    assert(l != NULL);
    assert(l->root != NULL);
    assert(element != NULL);

    memcpy(element, l->tail->data, l->element_size);
    node* prev = l->tail->prev;
    node* tmp = l->tail;
    if (prev != NULL) {
        prev->next = NULL;
        l->tail = prev;
    }
    else {
        l->root = NULL;
        l->tail = NULL;
    }

    node_free(tmp);
    l->count--;
}

void list_get(list* l, size_t index, void* element) {
    assert(l != NULL);
    assert(index < l->count);

    node* iter = l->root;
    for (size_t i = 0; i < index; ++i) {
        iter = iter->next;
    }

    assert(iter->data != NULL);
    memcpy(element, iter->data, l->element_size);
}

size_t list_count(list* l) {
    if (l == NULL) return 0;
    return l->count;
}
