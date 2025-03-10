#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct splay_node{
    struct splay_node* left;
    struct splay_node* right;
    struct splay_node* parent;
    int value;
}NODE;

typedef struct{
    NODE* root;
}TREE;

// === Splay ===

void rotate(NODE* parent, NODE* child) 
{
    if(!parent)
        return;

    NODE* root = parent->parent;

    if (root) {
        if (root->left == parent)
            root->left = child;
        else
            root->right = child;
    }

    if (parent->left == child) {
        parent->left = child->right;
        if (child->right)
            child->right->parent = parent;
        child->right = parent;
    } 
    else {
        parent->right = child->left;
        if (child->left)
            child->left->parent = parent;
        child->left = parent;
    }

    child->parent = root;
    parent->parent = child;
}

NODE* splay(NODE* node) 
{
    if(!node->parent)
        return node;

    NODE* parent = node->parent;
    NODE* root = parent->parent;

    if(!root) {
        rotate(parent, node);
        return node;
    } 
    else {
        bool zigzig = (root->left == parent) && (parent->left == node);

        if(zigzig) {
            rotate(root, parent);
            rotate(parent, node);
        } 
        else { // zigzag
            rotate(parent, node);
            rotate(root, node);
        }

        return splay(node);
    }
}

// === Support ===

void _delete_tree(NODE* node) 
{
    if (node) {
        _delete_tree(node->left);
        _delete_tree(node->right);
        free(node);
    }
}

NODE* _new_node(int value, NODE* parent) 
{
    NODE* temp = malloc(sizeof(NODE));
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = parent;
    temp->value = value;

    return temp;
}

NODE* _find_node(NODE* node, int value) 
{
    if (node == NULL)
        return node;

    if (node->value == value)
        return splay(node);

    if (node->value < value && node->right)
        return _find_node(node->right, value);
    else if(node->value > value && node->left)
        return _find_node(node->left, value);

    return splay(node);
}

void _set_parent(NODE* current, NODE* parent) 
{
    if(!current) 
        return;
    current->parent = parent;
}

void _keep_parent(NODE* current)
{
    _set_parent(current->left, current);
    _set_parent(current->right, current);
}

void split(NODE* root, int value, NODE** left, NODE** right) 
{
    if(root == NULL) {
        *left = NULL;
        *right = NULL;
        return;
    }

    root = _find_node(root, value);

    if(root->value == value) {
        _set_parent(root->left, NULL);
        _set_parent(root->right, NULL);

        *left = root->left;
        *right = root->right;
        return; 
    }

    if (root->value < value) {
        NODE* new_right = root->right;
        root->right = NULL;
        _set_parent(new_right, NULL);

        *left = root;
        *right = new_right;
        return;
    }
    else {
        NODE* new_left = root->left;
        root->left = NULL;
        _set_parent(new_left, NULL);

        *left = new_left;
        *right = root;
    }
}

NODE* merge(NODE* left, NODE* right) 
{
    if(!left)
        return right;

    if(!right)
        return left;

    NODE* min_right = right;
    while (min_right->left)
        min_right = min_right->left;

    min_right = splay(min_right);

    min_right->left = left;
    left->parent = min_right;

    return min_right;
}

// === Con/de-sturctor ===

void new_tree(TREE* tree) 
{
    tree->root = NULL;
}

void delete_tree(TREE* tree) 
{
    _delete_tree(tree->root);
    tree->root = NULL;
}

// === Useful functions ===

NODE* find_node(TREE* tree, int value)
{
    return _find_node(tree->root, value);
}

void add_node(TREE* tree, int value)
{
    NODE* left;
    NODE* right;

    split(tree->root, value, &left, &right);

    tree->root = _new_node(value, NULL);

    tree->root->left = left;
    tree->root->right = right;

    _keep_parent(tree->root);
}

void delete_node(TREE* tree, int value) 
{
    NODE* root = find_node(tree, value);

    if (!root)
        return;

    _set_parent(root->left, NULL);
    _set_parent(root->right, NULL);

    NODE* new_root = merge(root->left, root->right);
    free(root);

    tree->root = new_root;
}

// === Orders ===

void _inorder_dfs(NODE* node) 
{
    if (node) {
        _inorder_dfs(node->left);
        printf("%d ", node->value);
        _inorder_dfs(node->right);
    }
}

void _preorder_dfs(NODE* node) 
{
    if (node) {
        printf("%d ", node->value);
        _preorder_dfs(node->left);
        _preorder_dfs(node->right);
    }
}

void _postorder_dfs(NODE* node) 
{
    if (node) {
        _postorder_dfs(node->left);
        _postorder_dfs(node->right);
        printf("%d ", node->value);
    }
}

void inorder_dfs(TREE* tree) 
{
    _inorder_dfs(tree->root);
    printf("\n");
}

void postorder_dfs(TREE* tree) 
{
    _postorder_dfs(tree->root);
    printf("\n");
}

void preorder_dfs(TREE* tree) 
{
    _preorder_dfs(tree->root);
    printf("\n");
}

// === Main === 

int main() 
{
    TREE tree;
    TREE* p_tree = &tree;
    new_tree(p_tree);

    add_node(p_tree, 54);
    add_node(p_tree, 13);
    add_node(p_tree, 46);
    add_node(p_tree, 28);
    add_node(p_tree, 93);
    add_node(p_tree, 44);
    add_node(p_tree, 37);
    delete_node(p_tree, 28);
    inorder_dfs(p_tree);

    delete_tree(p_tree); 

    return 0;
}

