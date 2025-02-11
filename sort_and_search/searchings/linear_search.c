#include <stdio.h>

int linear_search(int arr[], int var, int n)
{
    for(int i = 0; i < n; i++){
        if(arr[i] == var) return i;
    }

    return -1;
}

int main()
{
    int arr[] = {10, 52, 2, 36, 18, 96, 5, 44, 17, 28};

    printf("%d", linear_search(arr, 2, 10));

    return 0;
}