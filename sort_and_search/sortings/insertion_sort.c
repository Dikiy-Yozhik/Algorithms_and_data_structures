#include <stdio.h>

void insertion_sort(int arr[], int n)
{
    for(int i = 1; i < n; i++){

        int var = arr[i];
        int j = i-1;

        while(j >= 0 && arr[j] > var){
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = var;
    }
}

int main()
{
    int arr[] = {64, 10, 25, 13, 84, 47};
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    insertion_sort(arr, n);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}