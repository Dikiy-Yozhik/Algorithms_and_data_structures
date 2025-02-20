#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linked_list_node{
    int value;
    struct linked_list_node* next;
}NODE;

typedef struct{
    NODE* head;
    int max;
}STACK;

void new_stack(STACK* stack)
{
    stack -> head = NULL;
}

void delete_stack(STACK* stack)
{
    NODE* temp = stack -> head;
    while(temp){
        NODE* current = temp;
        temp = temp -> next;
        free(current);
    }
}

bool is_empty(STACK* stack)
{
    return stack -> head == NULL;
}

int peek(STACK* stack)
{
    int var = stack -> head -> value;
    if(var > stack->max){
        var = stack -> max;
    }

    return var;
}

void push(STACK* stack, int var)
{
    bool flag = is_empty(stack);

    NODE* ptr = malloc(sizeof(NODE));
    ptr -> next = stack -> head;
    stack -> head = ptr;

    if(flag){
        ptr -> value = var;
        stack -> max = var;
    }

    else{
        if(var > stack->max){
            ptr -> value = 2 * var + stack->max;
            stack -> max = var;
        }
        else{
            ptr -> value = var;
        }
    }
}

int pop(STACK* stack)
{
    if(!is_empty(stack)){
        int var = stack -> head -> value;

        if(var > stack->max){
            var = stack->max;
            stack->max = stack->head->value - var*2;
        }

        NODE* current = stack -> head;
        stack -> head = current -> next;
        free(current);
        return var;
    }

    return 0;
}

void print_stack(STACK* stack)
{
    NODE* temp = stack -> head;
    while(temp){
        printf("%d ", temp -> value);
        temp = temp -> next;
    }
    printf("\n");
}

int main()
{
    STACK stack;
    STACK* ptr_stack = &stack;
    new_stack(ptr_stack);
    for(int i = 0; i < 20; i++) push(ptr_stack, i);
    print_stack(ptr_stack);
    printf("%d\n", ptr_stack->max);
    pop(ptr_stack);
    print_stack(ptr_stack);
    printf("%d\n", ptr_stack->max);
    delete_stack(ptr_stack);
    return 0;
}