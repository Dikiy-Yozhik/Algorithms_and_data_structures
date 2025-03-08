#include <stdio.h>

long long int search(long long int* array, long long int n, long long int target){
    long long int left = 0;
    long long int right = n-1;
    while(left <= right){
        long long int mid = left + (right - left) / 2;
        if(target <= array[mid] && (mid == 0 || target > array[mid-1])){ 
            return mid+1;
        }
        if(array[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}

int main(){
    long long int n, m, x;

    scanf("%lld", &n);

    long long int array[n];
    scanf("%lld", &array[0]);
    for(long long int i = 1; i < n; i++){
        scanf("%lld", &x);
        array[i] = array[i-1] + x;
    }

    scanf("%lld", &m);
    for(long long int i = 0; i < m; i++){
        scanf("%lld", &x);
        printf("%lld\n", search(array, n, x));
    }   

    return 0;
}