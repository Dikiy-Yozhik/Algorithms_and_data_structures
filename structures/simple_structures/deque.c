#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linked_list_node{
    int value;
    struct linked_list_node* next;
    struct linked_list_node* prev;
}NODE;

typedef struct{
    NODE* head;
    NODE* tail;
}DEQUE;

void new_deque(DEQUE* deque)
{
    deque -> head = NULL;
    deque -> tail = NULL;
}

void delete_deque(DEQUE* deque)
{
    NODE* temp = deque -> head;
    while(temp){
        NODE* current = temp;
        temp = temp -> next;
        free(current);
    }
}

bool is_empty(DEQUE* deque)
{
    return deque -> head == NULL;
}

void push_back(DEQUE* deque, int var)
{
    NODE* ptr = malloc(sizeof(NODE));
    ptr -> value = var;

    if(deque->head == NULL){
        deque -> head = ptr;
    }

    if(deque->tail != NULL){
        deque -> tail -> next = ptr;
    }

    ptr -> prev = deque -> tail;
    deque -> tail = ptr;
    ptr -> next = NULL;
}

void push_front(DEQUE* deque, int var)
{
    NODE* ptr = malloc(sizeof(NODE));
    ptr -> value = var;

    if(deque->head != NULL){
        deque -> head -> prev = ptr;
    }

    if(deque->tail == NULL){
        deque -> tail = ptr;
    }
    
    ptr -> next = deque -> head;
    deque -> head = ptr;
    ptr -> prev = NULL;
}

int pop_front(DEQUE* deque)
{
    if(!is_empty(deque)) {
        int var = deque -> head -> value;
        NODE* temp = deque -> head;

        if(deque->tail == deque->head) {
            deque->head = deque->tail->prev;
        }

        deque -> head = temp -> next;
        deque -> head -> prev = NULL;
        free(temp);
        return var;
    }

    return 0;
}

int pop_back(DEQUE* deque) 
{
    if(!is_empty(deque)) {
        int var = deque -> tail -> value;
        NODE* temp = deque -> tail;

        if(deque->tail == deque->head) {
            deque->head = deque->tail->prev;
        }

        deque -> tail = temp -> prev;
        deque -> tail -> next = NULL;
        free(temp);
        return var;
    }

    return 0;
}

void print_deque(DEQUE* deque)
{
    NODE* temp = deque -> head;
    while(temp){
        printf("%d ", temp -> value);
        temp = temp -> next;
    }
    printf("\n");
}

int main()
{
    DEQUE deque;
    DEQUE* ptr_q = &deque;
    new_deque(ptr_q);

    push_front(ptr_q, 10);
    push_front(ptr_q, 12);
    print_deque(ptr_q);

    push_back(ptr_q, 15);
    print_deque(ptr_q);

    pop_back(ptr_q);
    pop_front(ptr_q);

    print_deque(ptr_q);
    delete_deque(ptr_q);
    return 0;
}