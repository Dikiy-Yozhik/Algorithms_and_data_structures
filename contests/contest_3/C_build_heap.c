#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int first;
    int second;
}Pair;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down(int arr[], int n, int i, Pair** swaps, int* count){
    int root = i;

    int l_child = 2 * i + 1;
    int r_child = 2 * i + 2;

    if (l_child < n && arr[l_child] < arr[root]){
        root = l_child;
    }

    if (r_child < n && arr[r_child] < arr[root]){
        root = r_child;
    }
    
    if (root != i){
        swap(arr+i, arr+root);
        (*swaps)[(*count)].first = i;
        (*swaps)[(*count)].second = root;

        (*count)++;
        sift_down(arr, n, root, swaps, count);
    }
}

void build_min_heap(int* arr, int n, Pair** swaps, int* count){
    for (int i = n / 2 - 1; i >= 0; --i){ 
        sift_down(arr, n, i, swaps, count); 
    }
}

int main(){
    int n;
    scanf("%d", &n);

    int* arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int count = 0;
    Pair* swaps = malloc(n * sizeof(Pair));

    build_min_heap(arr, n, &swaps, &count);

    printf("%d\n", count);
    for(int i = 0; i < count; i++) printf("%d %d\n", swaps[i].first, swaps[i].second);

    free(arr);
    free(swaps);

    return 0;
}
