#include <stdio.h>

int ternary_search(int arr[], int len, int var)
{
    int l = 0;
    int r = len-1;

    while(l <= r){
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if(arr[m1] == var)
            return m1;
        if(arr[m2] == var)
            return m2;

        if(arr[m1] > var){
            r = m1 - 1;
        }

        else if(arr[m2] < var){
            l = m2 + 1;
        }

        else{
            l = m1 + 1;
            r = m2 - 1;
        }
    }

    return -1;
}


int main()
{
    int arr[] = {2, 5, 10, 17, 18, 28, 36, 44, 46, 96};

    printf("%d", ternary_search(arr, 10, 10));

    return 0;
}