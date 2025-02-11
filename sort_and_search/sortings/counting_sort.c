#include <stdio.h>
#include <stdlib.h>

void counting_sort(int arr[], int n)
{
    int max_el = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max_el)
            max_el = arr[i];
    }

    int* countArr = (int*)calloc((max_el + 1), sizeof(arr[0]));
    int* output = (int*)calloc(n, sizeof(arr[0]));

    for(int i = 0; i < n; i++)
        ++countArr[arr[i]];

    int k = 0;
    for(int i = 0; i < max_el+1; i++){
        while(countArr[i] != 0){
            output[k] = i;
            k++;
            countArr[i]--;
        }
    }

    for(int i = 0; i < n; i++)
        arr[i] = output[i];

    free(countArr);
    free(output);
}

int main()
{
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    counting_sort(arr, n);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}