#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int hoar_partition(int arr[], int l, int r)
{
    int pivot =  arr[(l+r)/ 2];
    int i = l, j = r;

    while(1)
    {
        while(arr[i] < pivot) i++;

        while(arr[j] > pivot) j--;

        if(i >= j) return j;

        swap(arr+i, arr+j);
        i++;
        j--;
    }
}


void quick_sort(int arr[], int l, int r)
{
    if(l < r)
    {
        int p = hoar_partition(arr, l, r);
        quick_sort(arr, l, p);
        quick_sort(arr, p+1, r);
    }
}


int main()
{
    int arr[] = {52, 33, 9, 0, 45, 21, 17, 14, 89, 42};

    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    quick_sort(arr, 0, n-1);

    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}