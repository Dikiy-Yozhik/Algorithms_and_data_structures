#include <stdio.h>

int binary_search(int* array, int n, int target){
    int left = 0;
    int right = n-1;
    while(left <= right){
        int mid = (right + left) / 2;
        printf("%d(%d) ", array[mid], mid);
        if(array[mid] == target){ 
            return mid;
        }
        if(array[mid] < target){
            left = mid + 1;
        }
        if(array[mid] > target){
            right = mid - 1;
        }
    }
    return -1;
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

    printf("Search history: ");

    int answer = binary_search(array, n, target);
    printf("\n");
    if(answer == -1){
        printf("No targets");
    }

    else{
        printf("Target is found at: %d", answer);
    }

    return 0;
}
