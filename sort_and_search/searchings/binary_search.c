#include <stdio.h>

int binary_search(int arr[], int len, int var)
{
    int l = 0;
    int r = len-1;

    while(l <= r){
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


int main()
{
    int arr[] = {2, 5, 10, 17, 18, 28, 36, 44, 46, 96};

    printf("%d", binary_search(arr, 10, 96));

    return 0;
}