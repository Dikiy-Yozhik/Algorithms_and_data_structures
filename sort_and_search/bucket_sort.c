#include <stdio.h>
#include <stdlib.h>

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

void bucket_sort(int arr[], int len, int start, int end, int n)
{
    int** buckets = malloc(n * sizeof(int*));
    int* b_indx = malloc(n * sizeof(int));

    int range = end - start;

    for(int i = 0; i < n; i++){
        buckets[i] = malloc(range/n * sizeof(int));
        b_indx[i] = 0;
    }
    
    for(int i = 0; i < len; i++){
        int index = (arr[i] * n) / range;
        buckets[index][b_indx[index]] = arr[i];
        b_indx[index]++;
    }

    int k = 0;
    for(int i = 0; i < n; i++){
        insertion_sort(buckets[i], b_indx[i]);

        for(int j = 0; j < b_indx[i]; j++){
            arr[k++] = buckets[i][j];
        }
    }
}

int main ()
{
    int arr[] = {26, 10, 25, 34, 7, 15, 30, 38, 37, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    bucket_sort(arr, n, 0, 40, 4);//Здесь start и end это концы интервала

    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}