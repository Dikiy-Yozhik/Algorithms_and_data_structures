#include <stdio.h>

void insertion_sort(int array[], int n){
    int count = 0;
    for(int i = 1; i < n; i++){
        int j = i - 1;
        int vstavka = array[i];
        while(j >= 0 && array[j] > vstavka){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = vstavka;
        count += 1;
        printf("Insertion - Element #%d\n", count);
        for(int z = 0; z < n; z++){
            printf("%d ", array[z]);
        }
        printf("\n");
    }
}

int main(){
    int n;
    scanf("%d", &n);
   
    int array[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    printf("Initial array:\n");
    for(int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }

    printf("\n");

    insertion_sort(array, n);

    return 0;
}