#include <stdio.h>

void selection_sort(int arr[], int n)
{
    for(int i = 0; i < n-1; i++){

        int min_indx = i;

        for(int j = i+1; j < n; j++){
            if(arr[j] < arr[min_indx])
                min_indx = j;
        }

        int temp = arr[i];
        arr[i] = arr[min_indx];
        arr[min_indx] = temp;
    }
}

int main()
{
    int arr[] = {64, 10, 25, 13, 84, 47};
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    selection_sort(arr, n);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}