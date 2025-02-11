#include <stdio.h>
#include <math.h>

int jump_search(int arr[], int var, int n)
{
    int l = 0;
    int r = sqrt(n);

    while(r < n && arr[r] <= var){
        l = r;
        r += sqrt(n);
        if(r > n-1) r = n;
    }
    
    for(; l < r; l++){
        if(arr[l] == var) return l;
    }

    return -1;
}

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("%d", jump_search(arr, 8, 10));

    return 0;
}