#include <stdio.h>

long long int maxArr(unsigned long long int* array, long long int n){
    long long int max = array[0];

    for(long long int i = 1; i < n; i++){
        if(array[i] > max) max = array[i];
    }

    return max;
}

int digit(long long int var){
    int k = -1;
    while(var > 0){
        var = var / 16;
        k++;
    }

    return k;
}

void counting_sort(unsigned long long int* array, long long int n, long long int digit){
    int digits[16] = {0};
    long long int sortArr[n];

    for(long long i = 0; i < n; i++){
        digits[array[i]/digit%16]++;
    }

    for(int i = 1; i < 16; i++){
        digits[i] += digits[i-1];
    }

    for(long long int i = n-1; i >= 0; i--){
        sortArr[digits[array[i]/digit%16]-1] = array[i];
        digits[array[i]/digit%16]--;
    }

    for(long long int i = 0; i < n; i++){
        array[i] = sortArr[i];
        printf("%llX\n", array[i]);
    }
}

void radix_sort(unsigned long long int* array, long long int n){
    long long int max_el = maxArr(array, n);
    int max_digit = digit(max_el);

    for(long long int digit = 1; max_el/digit > 0; digit*=16){
        printf("Sorting by %d digit:\n", max_digit);
        counting_sort(array, n, digit);
        printf("\n");
        max_digit--;
    }
}

int main(){
    long long int n;
    scanf("%lld", &n);

    unsigned long long int array[n];
    for(long long int i = 0; i < n; i++){
        scanf("%llx", &array[i]);
    }

    radix_sort(array, n);

    return 0;
}