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
}QUEUE;

void new_queue(QUEUE* queue)
{
    queue -> head = NULL;
    queue -> tail = NULL;
}

void delete_queue(QUEUE* queue)
{
    NODE* temp = queue -> head;
    while(temp){
        NODE* current = temp;
        temp = temp -> next;
        free(current);
    }
}

bool is_empty(QUEUE* queue)
{
    return queue -> head == NULL;
}

void enqueue(QUEUE* queue, int var)
{
    NODE* ptr = malloc(sizeof(NODE));
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

int dequeue(QUEUE* queue) 
{
    if(!is_empty(queue)) {
        int var = queue -> tail -> value;
        NODE* temp = queue -> tail;

        if(queue->tail == queue->head) {
            queue->head = queue->tail->prev;
        }

        queue -> tail = temp -> prev;
        queue -> tail -> next = NULL;
        free(temp);
        return var;
    }

    return 0;
}

void print_queue(QUEUE* queue)
{
    NODE* temp = queue -> head;
    while(temp){
        printf("%d ", temp -> value);
        temp = temp -> next;
    }
    printf("\n");
}

int main()
{
    QUEUE queue;
    QUEUE* ptr_q = &queue;
    new_queue(ptr_q);
    for(int i = 0; i < 20; i++) enqueue(ptr_q, i);
    print_queue(ptr_q);
    int d = dequeue(ptr_q);
    printf("%d\n", d);;
    printf("%d\n", ptr_q -> tail -> value);
    print_queue(ptr_q);
    delete_queue(ptr_q);
    return 0;
}