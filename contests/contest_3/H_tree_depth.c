#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    return a<b ? b : a;
}

int deep(int* arr, int* depth, int i){
    if(arr[i] == -1){
        return 1;
    }

    if(depth[arr[i]] == 0){
        depth[arr[i]] = deep(arr, depth, arr[i]);
    }

    return depth[arr[i]] + 1;
}

int main(){
    int n;
    scanf("%d", &n);

    int* arr = malloc(n * sizeof(int));
    int* depth = calloc(n, sizeof(int));
    int max_depth = 0;

    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    for(int i = 0; i < n; i++){
        if(depth[i] == 0){
            depth[i] = deep(arr, depth, i);
        }
        max_depth = max(max_depth, depth[i]);
    }

    printf("%d", max_depth);

    free(arr);
    free(depth);

    return 0;
}