#include <stdio.h>

int binary_search(int arr[], int start, int end, int var)
{
    int l = start;
    int r = end;

    while(l <= r)
    {
        int m = l + (r - l) / 2;
        if(arr[m] == var)
            return m;
        if(arr[m] > var)
            r = m - 1;
        if(arr[m] < var)
            l = m + 1;
    }

    return -1;
}


int exponential_search(int arr[], int len, int var)
{
    if(arr[0] == var)
        return 0;

    int i = 1;
    while(arr[i] < var && i < len){
        i *= 2;
    }

    i = (i < len-1) ? i : len-1;
    
    return binary_search(arr, i/2, i, var);
}


int main()
{
    int arr[] = {2, 5, 10, 17, 18, 28, 36, 44, 46, 96};

    printf("%d", exponential_search(arr, 10, 10));

    return 0;
}