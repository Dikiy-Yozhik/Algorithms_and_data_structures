#include <stdio.h>
#include <stdbool.h>

int linery_search(int* array, int n, int target){
    bool flag = false;
    int k = 1;
    for(int i = 0; i < n; i++){
        if(array[i] == target && k == 1){
            printf("Target is found at: %d", i);
            k++;
            flag = true;
        }

        else if(array[i] == target){
            printf(" %d", i);
        }
    }
    if(flag == false){
        printf("No targets");
    }
    return 0;
}

int main() {
    int n, target;
    scanf("%d %d", &n, &target);

    int array[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    printf("Initial array:\n");
    for(int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }

    printf("\n");

    printf("Target element: %d\n", target);

    linery_search(array, n, target);

    return 0;
}