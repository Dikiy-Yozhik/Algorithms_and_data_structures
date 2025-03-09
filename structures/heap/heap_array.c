#include <stdio.h>
#define MAX_SIZE 100

// === Support ===

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int heap[], int size, int i)
{
    int left_child = i*2 + 1;
    int right_child = i*2 + 2;

    int biggest = i;
    if(left_child < size && heap[i] < heap[left_child]){
        biggest = left_child;
    }
    if(right_child < size && heap[biggest] < heap[right_child]){
        biggest = right_child;
    }

    if(biggest != i){
        swap(heap+biggest, heap+i);
        heapify(heap, size, biggest);
    }
}

void delete(int heap[], int* size, int i)
{
    heap[i] = heap[*size-1];
    (*size)--;

    heapify(heap, *size, i);
}

// === Useful functions ===

void build_heap(int arr[], int size)
{
    for(int i = size/2 - 1; i >= 0; i--){
        heapify(arr, size, i);
    }
}

void add_node(int heap[], int* size, int var)
{
    if(*size == MAX_SIZE){
        printf("Heap overflow!\n");
        return;
    }

    heap[*size] = var;
    (*size)++;

    int i = *size - 1;
    while(i > 0)
    {
        if(heap[(i - 1) / 2] < heap[i])
        {
            swap(heap + (i - 1) / 2, heap + i);
            i = (i - 1) / 2;
        }
        else
            break;
    }
}

int get_max(int heap[], int* size)
{
    int max = heap[0];

    delete(heap, size, 0);

    return max;
}

// === Main ===

int main()
{
    int heap[MAX_SIZE];
    int size = 0;

    add_node(heap, &size, 1);
    add_node(heap, &size, 2);
    add_node(heap, &size, 3);
    add_node(heap, &size, 44);
    add_node(heap, &size, 5);
    add_node(heap, &size, 100);
    add_node(heap, &size, 7);
    add_node(heap, &size, 88);
    add_node(heap, &size, 9);
    add_node(heap, &size, 10);

    while (size != 0) {
        printf("%d ", get_max(heap, &size));
    }

    return 0;
}