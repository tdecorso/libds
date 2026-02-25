#include <stdio.h>
#include <stdbool.h>

#include "ds/bst.h"

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
    if (!node->data) return true;
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

int main(void) {

    printf("\n### Testing bst module...\n###\n");

    TEST(test_bst_node_alloc);
    TEST(test_bst_alloc);
    TEST(test_bst_free);

    printf("###\n### All tests passed. Bye! \n\n");

    return 0;
}
