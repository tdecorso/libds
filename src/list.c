#include "tds/list.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

list_node* list_node_alloc(size_t element_size) {
    assert(element_size != 0);

    list_node* n = malloc(sizeof(list_node));
    assert(n != NULL);

    n->data = malloc(element_size);
    assert(n->data != NULL);

    n->next = NULL;
    n->prev = NULL;

    return n;
}

void list_node_free(list_node* n) {
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

    list_node* iter = l->root;

    while (iter != NULL) {
        list_node* next = iter->next;
        list_node_free(iter);
        iter = next;
    }

    free(l);
}

void list_push_front(list* l, const void* element) {
    assert(l != NULL);
    assert(element != NULL);

    list_node* new_root = list_node_alloc(l->element_size);
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

    list_node* new_tail = list_node_alloc(l->element_size);
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

    list_node* tmp = l->root;
    if (l->root->next == NULL) {
        l->tail = NULL;
    }
    l->root = l->root->next;
    if (l->root != NULL) l->root->prev = NULL;
    list_node_free(tmp);
}

void list_pop_back(list* l, void* element) {
    assert(l != NULL);
    assert(l->root != NULL);
    assert(element != NULL);

    memcpy(element, l->tail->data, l->element_size);
    list_node* prev = l->tail->prev;
    list_node* tmp = l->tail;
    if (prev != NULL) {
        prev->next = NULL;
        l->tail = prev;
    }
    else {
        l->root = NULL;
        l->tail = NULL;
    }

    list_node_free(tmp);
    l->count--;
}

void list_get(list* l, size_t index, void* element) {
    assert(l != NULL);
    assert(index < l->count);

    list_node* n = list_node_at(l, index); 
    assert(n->data != NULL);
    memcpy(element, n->data, l->element_size);
}

size_t list_count(list* l) {
    if (l == NULL) return 0;
    return l->count;
}

list_node* list_node_at(list* l, size_t index) {
    assert(l != NULL);
    assert(index < l->count);

    list_node* iter = l->root;
    for (size_t i = 0; i < index; ++i) {
        iter = iter->next;
    }

    return iter;
}

void list_remove_at(list* l, size_t index, void* element) {
    assert(l != NULL);
    assert(index < l->count);
    assert(element != NULL);

    if (index == 0) {
        list_pop_front(l, element);
        return;
    }
    
    if (index == l->count - 1) {
        list_pop_back(l, element);
        return;
    }

    list_node* n = list_node_at(l, index);
    assert(n->data != NULL);
    memcpy(element, n->data, l->element_size);

    n->prev->next = n->next;
    n->next->prev = n->prev;
    list_node_free(n);
    l->count--;
}

void list_insert_at(list* l, size_t index, void* element) {
    assert(l != NULL);
    assert(index <= l->count);
    assert(element != NULL);

    if (index == 0) {
        list_push_front(l, element);
        return;
    }
    
    if (index == l->count) {
        list_push_back(l, element);
        return;
    }

    list_node* new_list_node = list_node_alloc(l->element_size);
    assert(new_list_node != NULL);
    memcpy(new_list_node->data, element, l->element_size);

    list_node* n = list_node_at(l, index);
    assert(n != NULL);
    new_list_node->prev = n->prev;
    n->prev->next = new_list_node;
    new_list_node->next = n;
    n->prev = new_list_node;
    l->count++;
}
