#include "ds/bst.h"

#include <assert.h>

bst* bst_alloc() {
    bst* tree = malloc(sizeof(bst));
    assert(tree != NULL);
    tree->root = NULL;
    tree->count = 0;
    return tree;
}

bst_node* bst_node_alloc() {
    bst_node* node = malloc(sizeof(bst_node));
    assert(node != NULL);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bst_node_free(bst_node* node) {
    if (node->left) bst_node_free(node->left);
    if (node->right) bst_node_free(node->right);

    free(node);
}

void bst_free(bst* tree) {
    if (tree->root) bst_node_free(tree->root);
    free(tree);
}

void bst_insert(bst* tree, int value) {
    assert(tree != NULL);
    if (!tree->root) {
        tree->root = bst_node_alloc();
        tree->root->data = value;
        tree->count++;
        return;
    }
    bst_node_insert(tree->root, value);
    tree->count++;
}

void bst_node_insert(bst_node* node, int value) {
    assert(node != NULL);
    if (value < node->data) {
        if (!node->left) {
            node->left = bst_node_alloc();
            node->left->data = value;
            return;
        }
        bst_node_insert(node->left, value);
    }
    else if (value >= node->data) {
        if (!node->right) {
            node->right = bst_node_alloc();
            node->right->data = value;
            return;
        }
        bst_node_insert(node->right, value);
    }
}

bool bst_search(bst* tree, int value) {
    assert(tree != NULL);
    if (!tree->root) return false;
    return bst_node_search(tree->root, value);
}

bool bst_node_search(bst_node* node, int value) {
    assert(node != NULL);
    if (node->data == value) return true;
    if (value < node->data && node->left) {
        return bst_node_search(node->left, value);
    }
    if (value > node->data && node->right) {
        return bst_node_search(node->right, value);
    }
    return false;
}
