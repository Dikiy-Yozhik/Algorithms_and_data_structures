#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node_t{
    int value;
    struct node_t* left;
    struct node_t* right;
}NODE;

typedef struct{
    NODE* root;
}TREE;

// === Support ==

void _delete_tree(NODE* node) 
{
    if (node) {
        _delete_tree(node->left);
        _delete_tree(node->right);
        free(node);
    }
}

NODE* _new_node(int value) 
{
    NODE* temp = malloc(sizeof(NODE));
    temp->left = NULL;
    temp->right = NULL;
    temp->value = value;

    return temp;
}

NODE* _add_node(NODE* node, int value) 
{
    if (!node)
        return _new_node(value);

    if (value < node->value)
        node->left = _add_node(node->left, value);
    else if (value > node->value)
        node->right = _add_node(node->right, value);

    return node;
}

NODE* _find_node(NODE* node, int value) {
    if (!node || node->value == value)
        return node;

    if (value < node->value)
        return _find_node(node->left, value);
    else
        return _find_node(node->right, value);
}

NODE* _successor(NODE* current) 
{
    current = current->right;
    while (current != NULL && current->left != NULL)
        current = current->left;

    return current;
}

NODE* _delete_node(NODE* root, int value) 
{
    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = _delete_node(root->left, value);
    else if (value > root->value)
        root->right = _delete_node(root->right, value);
    else {
        if (root->left == NULL) {
            NODE* temp = root->right;
            free(root);
            return temp;
        } 
        else if (root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return temp;
        }

        NODE* temp = _successor(root);
        root->value = temp->value;
        root->right = _delete_node(root->right, temp->value);
    }

    return root;
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
    tree->root = _add_node(tree->root, value);
}

void delete_node(TREE* tree, int value) 
{
    tree->root = _delete_node(tree->root, value);
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