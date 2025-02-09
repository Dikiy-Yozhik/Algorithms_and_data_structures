#include <stdio.h>

void bubble_sort(int arr[], int n)
{
    for(int i = 0; i < n-1; i++){

        int flag = 0;

        for(int j = 0; j < n; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = 1;
            }
        }

        if(flag == 0) break;
    }
}

int main()
{
    int arr[] = {64, 10, 25, 13, 84, 47};
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    bubble_sort(arr, n);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}