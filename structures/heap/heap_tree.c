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

// === QUEUE ===
typedef struct linked_list_node{
    NODE* value;
    struct linked_list_node* next;
    struct linked_list_node* prev;
}linked_list_node;

typedef struct{
    linked_list_node* head;
    linked_list_node* tail;
}QUEUE;

void new_queue(QUEUE* queue)
{
    queue -> head = NULL;
    queue -> tail = NULL;
}

void delete_queue(QUEUE* queue)
{
    linked_list_node* temp = queue->head;
    while (temp) {
        linked_list_node* current = temp;
        temp = temp->next;
        free(current);
    }
    queue->head = NULL; 
    queue->tail = NULL; 
}

bool is_empty(QUEUE* queue)
{
    return queue -> head == NULL;
}

void enqueue(QUEUE* queue, NODE* var)
{
    linked_list_node* ptr = malloc(sizeof(linked_list_node));
    ptr -> value = var;

    if(queue->head != NULL){
        queue -> head -> prev = ptr;
    }

    if(queue->tail == NULL){
        queue -> tail = ptr;
    }
    
    ptr -> next = queue -> head;
    queue -> head = ptr;
    ptr -> prev = NULL;
}

NODE* dequeue(QUEUE* queue) 
{
    if (!is_empty(queue)) {
        NODE* var = queue->tail->value;
        linked_list_node* temp = queue->tail;

        queue->tail = temp->prev;

        if(queue->tail)
            queue->tail->next = NULL; 
        else 
            queue->head = NULL;        

        free(temp);
        return var;
    }

    return NULL;
}

// === Support ===

void _delete_tree(NODE* node)
{
    if(node){
        _delete_tree(node->left);
        _delete_tree(node->right);
        free(node);
    }
}

bool _node_exist(NODE* node, int value)
{
    if (!node)
        return false;
    if (node->value == value)
        return true;

    return _node_exist(node->left, value) || _node_exist(node->right, value);
}

NODE* _find_node(NODE* node, int value)
{
    if(!node)
        return NULL;
    else if(node->value == value)
        return node;

    NODE* res = _find_node(node->left, value);
    if(!res)
        res = _find_node(node->right, value);

    return res;
}

NODE* _find_first_with_leaf(NODE* node) {
    if(!node){
        return NULL;
    } 
    else{
        if(node->left && !node->left->left && !node->left->right){
            return node;
        }

        if(node->right && !node->right->left && !node->right->right){
            return node;
        }
    }

    NODE* res = _find_first_with_leaf(node->left);

    if(res){
        return res;
    }

    return _find_first_with_leaf(node->right);
}

void _inorder_dfs(NODE* node)
{
    if(node){
        _inorder_dfs(node->left);
        printf("%d ", node->value);
        _inorder_dfs(node->right);
    }
}

void _preorder_dfs(NODE* node)
{
    if(node){
        printf("%d ", node->value);
        _preorder_dfs(node->left);
        _preorder_dfs(node->right);
    }
}

void _postorder_dfs(NODE* node)
{
    if(node){
        _postorder_dfs(node->left);
        _postorder_dfs(node->right);
        printf("%d ", node->value);
    }
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
    if(!tree->root){
        tree->root = malloc(sizeof(NODE));
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->root->value = value;
        return;
    }

    QUEUE queue;
    QUEUE* p_queue = &queue;
    new_queue(p_queue);

    enqueue(p_queue, tree->root);

    while(!is_empty(p_queue))
    {
        NODE* node = dequeue(p_queue);

        if(node->left)
            enqueue(p_queue, node->left);
        else{
            node->left = malloc(sizeof(NODE));
            node->left->left = NULL;
            node->left->right = NULL;
            node->left->value = value;
            break;
        }

        if(node->right)
            enqueue(p_queue, node->right);
        else{
            node->right = malloc(sizeof(NODE));
            node->right->left = NULL;
            node->right->right = NULL;
            node->right->value = value;
            break;
        }
    }

    delete_queue(p_queue);
}

void delete_node(TREE* tree, int value) 
{
    NODE* to_del = find_node(tree, value);
    if (!to_del)
        return;

    if (to_del == tree->root) {
        if (!to_del->left && !to_del->right) {
            free(to_del);
            tree->root = NULL;
            return;
        }
    }

    NODE* temp = _find_first_with_leaf(tree->root);
    if (!temp)
        return;

    NODE* leaf;
    if (temp->left) {
        leaf = temp->left;
        temp->left = NULL;
    } else {
        leaf = temp->right;
        temp->right = NULL;
    }

    to_del->value = leaf->value;
    free(leaf);
}

void inorder_dfs(TREE* tree)
{
    _inorder_dfs(tree->root);
}

void postorder_dfs(TREE* tree)
{
    _postorder_dfs(tree->root);
}

void preorder_dfs(TREE* tree)
{
    _preorder_dfs(tree->root);
}

// === Heap functions ===

void heapify_subtree(NODE* node) 
{
    if(!node)
        return;

    if(node->left == NULL && node->right == NULL)
        return;

    NODE* biggest = node;

    if(node->left && node->left->value > biggest->value)
        biggest = node->left;

    if(node->right && node->right->value > biggest->value) {
        biggest = node->right;
    }

    if(biggest == node) 
        return;
    else{
        int temp = biggest->value;
        biggest->value = node->value;
        node->value = temp;

        heapify_subtree(biggest);
    }
}

void _heapify(NODE* node) {
    if(!node)
        return;

    _heapify(node->left);
    _heapify(node->right);

    heapify_subtree(node);
}

void heapify(TREE* tree) 
{
    _heapify(tree->root);
}

int get_max(TREE* tree) 
{
    if(tree->root){
        int max = tree->root->value;
        delete_node(tree, max);
        if(tree->root){
            heapify_subtree(tree->root);
        }
        return max;
    }
    return 0;
}

// === Main ===

int main() {

    TREE tree;
    TREE* p_tree = &tree;

    new_tree(p_tree);

    add_node(p_tree, 1);
    add_node(p_tree, 2);
    add_node(p_tree, 3);
    add_node(p_tree, 44);
    add_node(p_tree, 5);
    add_node(p_tree, 100);
    add_node(p_tree, 7);
    add_node(p_tree, 88);
    add_node(p_tree, 9);
    add_node(p_tree, 10);

    heapify(p_tree);

    while(p_tree->root){
        printf("%d ", get_max(p_tree));
    }

    delete_tree(p_tree);

    return 0;
}