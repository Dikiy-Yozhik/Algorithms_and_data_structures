#include <stdio.h>
#include <stdlib.h>

typedef struct{
    long long int index;
    long long int time;
} Pair;

void swap(Pair* a, Pair* b){
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down(Pair* arr, long long int n, long long int i){
    long long int root = i;

    long long int l_child = 2 * i + 1;
    long long int r_child = 2 * i + 2;

    if ((l_child < n) && ((arr[l_child].time < arr[root].time) || (arr[l_child].time == arr[root].time && arr[l_child].index < arr[root].index))){
        root = l_child;
    }

    if ((r_child < n) && ((arr[r_child].time < arr[root].time) || (arr[r_child].time == arr[root].time && arr[r_child].index < arr[root].index))){
        root = r_child;
    }
    
    if (root != i){
        swap(arr + i, arr + root);
        sift_down(arr, n, root);
    }
}

int main(){
    long long int n, m;
    scanf("%lld %lld", &n, &m);

    Pair* procces = malloc(n * sizeof(Pair));
    for(long long int i = 0; i < n; i++){
        procces[i].index = i;
        procces[i].time = 0;
    }


    long long int* tasks = malloc(m * sizeof(long long int));
    for(long long int i = 0; i < m; i++){
        scanf("%lld", &tasks[i]);
    }

    for(long long int i = 0; i < m; i++){
        printf("%lld %lld\n", procces[0].index, procces[0].time);
        procces[0].time += tasks[i];
        sift_down(procces, n, 0);
    }

    free(procces);
    free(tasks);
    return 0;
}