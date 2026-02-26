#include <stdio.h>
#include <stdbool.h>

#include "tds/bst.h"

#define TEST(fun)                          \
    do {                                   \
        if ((fun)()) {                     \
            printf("### Test failed.\n");  \
            return 1;                      \
        }                                  \
    } while(0)


bool test_bst_node_alloc() {
    printf("### Testing bst node alloc...\n");

    bst_node* node = bst_node_alloc();

    if (!node) return true;
    if (node->data) return true;
    if (node->left) return true;
    if (node->right) return true;

    bst_node_free(node);

    return false;
}

bool test_bst_alloc() {
    printf("### Testing bst alloc...\n");

    bst* tree = bst_alloc();

    if (!tree) return true;
    if (tree->root) return true;
    if (tree->count != 0) return true;

    bst_free(tree);

    return false;
}

bool test_bst_free() {
    printf("### Testing bst free...\n");

    bst* tree = bst_alloc();
    bst_free(tree);
    
    tree = NULL;

    return false;
}

bool test_bst_insert() {
    printf("### Testing bst insert...\n");

    bst* tree = bst_alloc();

    bst_insert(tree, 2);
    if (tree->root->data != 2) return true;
    if (tree->count != 1) return true;
    bst_insert(tree, 1);
    if (tree->root->left->data != 1) return true;
    if (tree->count != 2) return true;
    bst_insert(tree, 3);
    if (tree->root->right->data != 3) return true;
    if (tree->root->data != 2) return true;
    if (tree->count != 3) return true;
    bst_insert(tree, 4);
    if (tree->root->right->right->data != 4) return true;

    bst_free(tree);

    return false;
}

bool test_bst_search() {
    printf("### Testing bst search...\n");

    bst* tree = bst_alloc();

    bst_insert(tree, 1);
    bst_insert(tree, 2);
    bst_insert(tree, 0);

    if (!bst_search(tree, 1)) return true;
    if (!bst_search(tree, 2)) return true;
    if (!bst_search(tree, 0)) return true;
    if ( bst_search(tree, 4)) return true;

    bst_free(tree);

    return false;
}

int main(void) {

    printf("\n### Testing bst module...\n###\n");

    TEST(test_bst_node_alloc);
    TEST(test_bst_alloc);
    TEST(test_bst_free);
    TEST(test_bst_insert);
    TEST(test_bst_search);

    printf("###\n### All tests passed. Bye! \n\n");

    return 0;
}
