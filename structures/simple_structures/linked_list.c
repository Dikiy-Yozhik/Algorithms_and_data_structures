#include <stdio.h>
#include <stdlib.h>

// Data structure
typedef struct _linked_list_node{
    int value;
    struct _linked_list_node* next;
}node;

typedef struct{
    node* head;
    node* tail;
}linked_list;


// Constructor and distructor
linked_list* new_list(int var)
{
    linked_list* list = malloc(sizeof(linked_list));
    node* ptr = malloc(sizeof(node));
    ptr -> value = var;
    ptr -> next = NULL;
    list -> head = ptr;
    list -> tail = ptr;
    return list;
}

void delete_list(linked_list* list)
{
    node* temp = list -> head;
    while(temp){
        node* current = temp;
        temp = temp -> next;
        free(current);
    }
}

// Search
node* get_node_value(linked_list* list, int var)
{
    node* temp = list -> head;
    while(temp->next)
    {
        if(temp -> value == var)
            return temp;
        
        temp = temp -> next;
    }
    return NULL;
}

// Insert
void insert_head(linked_list* list, int var)
{
    node* ptr = malloc(sizeof(node));
    ptr -> value = var;
    ptr -> next = list -> head;
    list -> head = ptr;
}

void insert_tail(linked_list* list, int var){
    node* ptr = malloc(sizeof(node));
    ptr -> value = var;
    ptr -> next = NULL;
    list -> tail -> next = ptr;
    list -> tail = ptr;
}


void insert_after_value(linked_list* list, int after_var, int var)
{
    node* after = get_node_value(list, after_var);

    node* ptr = malloc(sizeof(node));
    ptr -> value = var;
    ptr -> next = after -> next;
    after -> next = ptr;
}


// Delete
void delete_node(linked_list* list, int var)
{
    node* temp = list -> head;

    if(temp -> value == var){
        list -> head = temp -> next;
        free(temp);
        return;
    }

    while(temp -> next){
        if(temp -> next -> value == var){
            node* ptr = temp -> next;
            temp -> next = ptr -> next;
            free(ptr);
            break;
        }

        temp = temp -> next;
    }
}


// printing
void print_list(linked_list* list) {
    node* temp = list->head;

    while (temp) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    printf("\n");
}


int main()
{
    linked_list* list = new_list(23);
    insert_head(list, 24);
    for(int i = 0; i < 20; i++){
        insert_tail(list, i);
    }
    print_list(list);
    delete_list(list);
    return 0;
}