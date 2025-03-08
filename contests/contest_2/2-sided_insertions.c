#include <stdio.h>

void double_insertion_sort(long long int array[], long long int n){
    int count = 0;
    long long int kolvo = n/2;

    for(long long int i = 1; i < kolvo; i++){
        long long int l = i - 1;
        long long int vstavka_l = array[i];
        while(l >= 0 && array[l] > vstavka_l){
            array[l+1] = array[l];
            l--;
        }
        array[l+1] = vstavka_l;

        long long int r = n - i;
        long long int vstavka_r = array[n-i-1];
        while(r < n && array[r] > vstavka_r){
            array[r-1] = array[r];
            r++;
        }
        array[r-1] = vstavka_r;

        count += 1;
        printf("Step %d:\n", count);
        for(long long int z = 0; z < n; z++){
            printf("%d ", array[z]);
        }
        printf("\n");
    }
}

int main(){
    long long int n;
    scanf("%lld", &n);
   
    long long int array[n];
    for(long long int i = 0; i < n; i++){
        scanf("%lld", &array[i]);
    }

    printf("Step 0:\n");
    for(long long int i = 0; i < n; i++){
        printf("%lld ", array[i]);
    }

    printf("\n");

    double_insertion_sort(array, n);

    return 0;
}