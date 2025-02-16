#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int len;
    int max_size;
    int* arr;
}STACK;

void new_stack(STACK* stack, int size)
{
    stack -> arr = malloc(size * sizeof(int));
    stack -> max_size = size;
    stack -> len = 0;
}

void delete_stack(STACK* stack)
{
    free(stack -> arr);
}

bool is_empty(STACK* stack)
{
    return stack -> len == 0;
}

bool is_full(STACK* stack)
{
    return stack->len == stack->max_size;
}

int peek(STACK* stack)
{
    return stack -> arr[stack->len - 1];
}

void push(STACK* stack, int var)
{
    if(!is_full(stack)){
        stack -> arr[stack->len] = var;
        stack -> len++;
    }
}

int pop(STACK* stack)
{
    if(!is_empty(stack)){
        stack -> len--;
        return stack->arr[stack->len];
    }
    return 0;
}

void print_stack(STACK* stack)
{
    for(int i = 1; i <= stack->len; i++){
        printf("%d ", stack->arr[i-1]);
    }
    printf("\n");
}

int main()
{
    STACK stack;
    STACK* ptr_stack = & stack;
    new_stack(ptr_stack, 20);
    for(int i = 0; i < 20; i++) push(ptr_stack, i);
    print_stack(ptr_stack);
    pop(ptr_stack);
    print_stack(ptr_stack);
    delete_stack(ptr_stack);
    return 0;
}