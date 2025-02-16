#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int len;
    int max_size;
    int* arr;
}QUEUE;

void new_queue(QUEUE* queue, int size)
{
    queue -> arr = malloc(size * sizeof(int));
    queue -> max_size = size;
    queue -> len = 0;
}

void delete_queue(QUEUE* queue)
{
    free(queue -> arr);
}

bool is_empty(QUEUE* queue)
{
    return queue -> len == 0;
}

bool is_full(QUEUE* queue)
{
    return queue->len == queue->max_size;
}

void print_queue(QUEUE* queue)
{
    for(int i = 1; i <= queue->len; i++){
        printf("%d ", queue->arr[i-1]);
    }
    printf("\n");
}

void enqueue(QUEUE* queue, int var)
{
    if(!is_full(queue)){
        queue -> arr[queue->len] = var;
        queue->len++;
    }
}

int dequeue(QUEUE* queue)
{
    if(!is_empty(queue)){
        int var = queue->arr[0];
        for(int i = 0; i < queue->len; i++) 
            queue->arr[i] = queue->arr[i+1];
        queue->len--;
        return var;
    }
}

int main()
{
    QUEUE queue;
    QUEUE* ptr_queue = & queue;
    new_queue(ptr_queue, 20);
    for(int i = 0; i < 20; i++) enqueue(ptr_queue, i);
    print_queue(ptr_queue);
    dequeue(ptr_queue);
    print_queue(ptr_queue);
    delete_queue(ptr_queue);
    return 0;
}