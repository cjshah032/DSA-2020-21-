//////// header file definitions //////////////
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
//////////////////////////////////////////////

/////// structure definitions ////////////////
typedef struct node{
    int key;
    struct node* left, *right;
    int x:2;
} treenode;
//////////////////////////////////////////////

////// function declarations /////////////////
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
/////////////////////////////////////////////

////// generic function definitions /////////
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
/////////////////////////////////////////////

////// balanced tree function definitions ///
/*
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
            else {
                if(root->left->left != NULL)
                    rotate(root->left->left, root->left, root);
                else rotate(root->left->right, root->left, root);
            }
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

            else {
                if(root->right->left != NULL)
                    rotate(root->right->left, root->right, root);
                else rotate(root->right->right, root->right, root);
            }
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
            else {
                if(root->right->left != NULL)
                    rotate(root->right->left, root->right, root);
                else rotate(root->right->right, root->right, root);
            }
        }

        else if(key > root->key)
        {
            root->right = tree_delete(root->right, key);
            if(root->x > -1)
                root->x --;
            else {
                if(root->left->left != NULL)
                    rotate(root->left->left, root->left, root);
                else rotate(root->left->right, root->left, root);
            }   
        }

        else {
            if(root->right != NULL) 
            {
                treenode* t = tree_minimum(root->right);
                root->key = t->key;
                root->right = tree_delete(root->right, t->key);
                if(root->x != -1)
                    root->x --;
                else {
                    if(root->left->left != NULL)
                        rotate(root->left->left, root->left, root);
                    else rotate(root->left->right, root->left, root);
                }
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
*/
/////////////////////////////////////////////

////// unbalanced tree function definitions /
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
/////////////////////////////////////////////

//////// driver function ////////////////////
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
////////////////////////////////////////////
//////// END OF ASSIGNMENT /////////////////
////////////////////////////////////////////