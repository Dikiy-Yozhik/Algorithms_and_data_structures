#include <stdio.h>
#include <stdlib.h>

typedef struct node_avl{
    struct node_avl* left;
    struct node_avl* right;
    int height;
    int value;
}NODE;

typedef struct avl_tree{
    NODE* root;
}TREE;

// === Balance support ===

int _height(NODE* node)
{
    if (node)
        return node->height;
    else
        return 0;
}

int _bfactor(NODE* node)
{
    if (node)
        return _height(node->right) - _height(node->left);
    else
        return 0;
}

void _fix_height(NODE* node) {
    int height_left = _height(node->left);
    int height_right = _height(node->right);

    if (height_left > height_right)
        node->height = height_left + 1;
    else 
        node->height = height_right + 1;
}

// === Balance ===

NODE* rotate_right(NODE* node)
{
    NODE* left = node->left;
    node->left = left->right;
    left->right = node;

    _fix_height(node);
    _fix_height(left);

    return left;
}

NODE* rotate_left(NODE* node)
{
    NODE* right = node->right;
    node->right = right->left;
    right->left = node;

    _fix_height(node);
    _fix_height(right);

    return right;
}

NODE* balance(NODE* node)
{
    if (node == NULL)
        return node;

    _fix_height(node);

    if (_bfactor(node) == 2) {
        if (_bfactor(node->right) < 0)
            node->right = rotate_right(node->right);

        return rotate_left(node);
    }

    if (_bfactor(node) == -2) {
        if (_bfactor(node->left) > 0)
            node->left = rotate_left(node->left);

        return rotate_right(node);
    }

    return node;
}

// === Support ===

void _delete_tree(NODE* node)
{
    if (node == NULL)
        return;

    _delete_tree(node->left);
    _delete_tree(node->right);

    free(node);
}

NODE* _new_node(int value)
{
    NODE* temp = malloc(sizeof(NODE));
    temp->left = NULL;
    temp->right = NULL;
    temp->value = value;
    _fix_height(temp);

    return temp;
}

NODE* _add_node(NODE* node, int value)
{
    if (node == NULL)
        return _new_node(value);
    if (node->value == value)
        return node;

    if (value < node->value)
        node->left = _add_node(node->left, value);
    else
        node->right = _add_node(node->right, value);

    return balance(node);
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
            return balance(temp);
        } 
        else if (root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return balance(temp);
        }

        NODE* temp = _successor(root);
        root->value = temp->value;
        root->right = _delete_node(root->right, temp->value);
    }

    return balance(root);
}

// === Con/de-structor

void new_tree(TREE* tree)
{
    tree->root = NULL;
}

void delete_tree(TREE* tree)
{
    _delete_tree(tree->root);
}

// === Useful functions ===

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