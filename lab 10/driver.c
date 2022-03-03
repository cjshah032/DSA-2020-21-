#include "tree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    treenode* root = createNode(5);
    tree_add(root, 2);
    tree_add(root, 1);
    tree_add(root, 8);
    tree_add(root, 10);
    tree_add(root, 4);
    tree_add(root, 6);
    tree_add(root, 7);

    inOrderTraversal(root);
    root = tree_delete(root, 8);
    root = tree_delete(root, 10);
    root = tree_delete(root, 5);
    root = tree_delete(root, 2);
    root = tree_delete(root, 1);
    root = tree_delete(root, 4);
    root = tree_delete(root, 6);
    root = tree_delete(root, 7);

    assert(root == NULL);
    return 0;
}