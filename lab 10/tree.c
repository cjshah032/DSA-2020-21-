#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

treenode* createNode(int key)
{
    treenode* t = (treenode*) malloc(sizeof(treenode));
    t->key = key;
    t->left = NULL;
    t->right = NULL;
    t->x = 0;
}

void treenode_copy(treenode* a, treenode* b)
{
    a->key = b->key;
    a->left = b->left;
    a->right = b->right;
    a->x = b->x;
}

void inOrderTraversal(treenode* root)
{   
    if(root == NULL)
        return;
    inOrderTraversal(root->left);
    printf("%d ", root->key);
    inOrderTraversal(root->right);
}

int isLeaf(treenode* node)
{
    if(node->left != NULL || node->right != NULL)
        return 0;
    return 1;
}

treenode* tree_find(treenode* root, int key)
{
    if(root == NULL || root->key == key)
        return root;
    if(key < root->key)
        return tree_find(root->left, key);
    return tree_find(root->right, key);
}

treenode* tree_minimum(treenode* root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

treenode* find_successor(treenode* root, treenode* node)
{
    if(node->right != NULL)
        return tree_minimum(node->right);
    
    treenode* succ = NULL;
    while (root != NULL)
    {
        if(node->key < root->key)
        {
            succ = root;
            root = root->left;
        }

        else if(node->key > root->key)
            root = root->right;

        else break;
    }
    
    return succ;
}

treenode* find_parent(treenode* root, treenode* node)
{
    treenode* succ = NULL;
    while(root != NULL)
    {
        if(root->key < node->key)
        {
            succ = root;
            root = root->right;
        }
        else if(root->key > node->key)
        {
            succ = root;
            root = root->left;
        }
        else break;
    }

    return succ;
}


void rotate(treenode* x, treenode* y, treenode* z)
{
    // z - root node where imbalance occurs
    // y - child of z at the side where imbalance occurs
    // x - any non-null child of y
    treenode *a, *b, *c, *t;

    /// ordering x,y,z as a,b,c
    a = x; b = y; c = z;
    if(a->key > b->key)
    {
        t = b;
        b = a;
        a = t;
    }
    if(a->key > c->key)
    {
        t = c;
        c = a;
        a = c;
    }
    if(b->key > c->key)
    {
        t = b;
        b = c;
        c = t;
    }

    // identifying t0,t1,t2,t3 
    treenode* t0, *t1, *t2, *t3;
    t0 = a->left;
    t1 = (a == x ? a->right : b->left);
    t2 = (c == x ? c->left : b->right);
    t3 = c->right;

    // performing rotation
    z->left = x;        // assigning irrespective of a,b,c, then 
    z->right = y;       // changing the keys

    int k1 = a->key, k2 = b->key, k3 = c->key;
    z->key = k2;
    x->key = k1;
    y->key = k3;
    x->left = t0;       // assigning the subtrees
    x->right = t1;
    y->left = t2;
    y->right = t3;
    z->x = 0;           // correcting imbalances after rotation
    x->x = 0;
    y->x = 0;
}   


