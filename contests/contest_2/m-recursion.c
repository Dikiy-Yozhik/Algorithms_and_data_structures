#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int dec_to_bin(int* array, int i, long long int dec){
    while(dec > 0){
        array[i] = dec%2;
        i++;
        dec = dec/2;
        
    }
    return i;
}

int print_Binary(int* array, int* reverse_arr, int i, int k){
    printf("%d", array[i-1]); 
    reverse_arr[0] = array[i-1];
    k++;

    for(int j = i-2; j >= 0; j--){ 
        if(array[j] != array[j+1]){ 
            printf("%d", array[j]); 
            reverse_arr[k] = array[j];
            k++;
        } 
        else{ 
            array[j] = abs(array[j-1] - 1); 
        } 
    } 

    printf("\n"); 
    return k;
}
    

int main(){
    int bin[64];
    int reverse_bin[64];
    int i = 0;
    int k = 0;
    long long int n;

    scanf("%lld", &n);

    i = dec_to_bin(bin, i, n);

    k = print_Binary(bin, reverse_bin, i, k);

    for(int j = k-1; j >= 0; j--){
        printf("%d", reverse_bin[j]);
    }

    return 0;
}