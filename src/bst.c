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
    node->data = malloc(sizeof(int));
    assert(node->data != NULL);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bst_node_free(bst_node* node) {
    if (node->left) bst_node_free(node->left);
    if (node->right) bst_node_free(node->right);

    free(node->data);
    free(node);
}

void bst_free(bst* tree) {
    if (tree->root) bst_node_free(tree->root);
    free(tree);
}
