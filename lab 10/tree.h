#pragma once

typedef struct node{
    int key;
    struct node* left, *right;
    int x:2;
} treenode;

treenode* createNode(int key);

void treenode_copy(treenode* a, treenode* b);

void inOrderTraversal(treenode* root);

void tree_add(treenode* root, int key);

treenode* tree_find(treenode* root, int key);

int isLeaf(treenode* node);

treenode* tree_minimum(treenode* root);

treenode* find_parent(treenode* root, treenode* node);

treenode* find_successor(treenode* root, treenode* node);

treenode* tree_delete(treenode* root, int key);

void rotate(treenode* x, treenode* y, treenode* z);