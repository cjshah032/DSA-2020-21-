#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void tree_add(treenode* root, int key)
{
    if(key < root->key)
    {
        if(root->left == NULL)
        {
            treenode* t = createNode(key);
            root->left = t;
        }

        else tree_add(root->left, key);
       
        if(root->x > -1)
            root->x --;
    }
    
    else if(key > root->key) {
        if(root->right == NULL)
        {
            treenode* t = createNode(key);
            root->right = t;
        }

        else tree_add(root->right, key);
       
        if(root->x < 1)
            root->x ++;
    }
}

treenode* tree_delete(treenode* root, int key)
{
    if(root == NULL)
        return NULL;

    if(key < root->key)
    {
        root->left = tree_delete(root->left, key);
        if(root->x < 1)
            root->x++;
    }

    else if(key > root->key)
    {
        root->right = tree_delete(root->right, key);
        if(root->x > -1)
            root->x --;
    }

    else {
        if(root->right != NULL) 
        {
            treenode* t = tree_minimum(root->right);
            root->key = t->key;
            root->right = tree_delete(root->right, t->key);
            if(root->x > -1)
                root->x --;
        }

        else if(root->left != NULL)
        {
            treenode* temp = root->left;
            treenode_copy(root, root->left);
            free(temp);
        }

        else 
        {
            free(root);
            return NULL;
        }
    }

    return root;
}