#include <stdio.h>

int partition(int* array, int left, int right){
    int pivot = array[(left + right) / 2];
    printf("Pivot index: %d , pivot element: %d\n", (left+right)/2, pivot);
    
    while(1){
        while(array[left] < pivot){
            left++;
        }

        while (array[right] > pivot)
        {
            right--;
        }
        
        if(left >= right){
            return right;
        }

        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;

    }
}


void quik_sort(int* array, int start, int end, int n){
    if(start < end){
        int pivot = partition(array, start, end);
        printf("Array after partition:");
        for(int i = 0; i < n; i++){
            printf(" %d", array[i]);
        } 
        printf("\n\n");
        quik_sort(array, start, pivot, n);
        quik_sort(array, pivot+1, end, n);
    }
}



int main(){
    int n;
    scanf("%d", &n);

    int array[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    printf("Initial array:\n");

    for(int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }   

    printf("\n\n");

    quik_sort(array, 0, n-1, n);

    return 0;
}