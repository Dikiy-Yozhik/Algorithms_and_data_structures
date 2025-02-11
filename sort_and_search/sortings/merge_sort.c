#include <stdio.h>
#include <stdlib.h>


void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int* Left = malloc(n1 * sizeof(int));
    int* Right = malloc(n2 * sizeof(int));

    for(int i = 0; i < n1; i++) 
        Left[i] = arr[l+i];
    for(int j = 0; j < n2; j++)
        Right[j] = arr[m+j+1];

    int i = 0;
    int j = 0;
    int k = l;
    
    while(i < n1 && j < n2)
    {
        if(Left[i] <= Right[j]){
            arr[k] = Left[i];
            i++;
        }

        else if(Right[j] < Left[i]){
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        arr[k++] = Left[i++];
    }

    while(j < n2)
    {
        arr[k++] = Right[j++];
    }

    free(Left);
    free(Right);
}


void merge_sort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}


int main()
{
    int arr[] = {52, 33, 9, 0, 45, 21, 17, 14, 89, 42};

    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    merge_sort(arr, 0, n-1);

    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}