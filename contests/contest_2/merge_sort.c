#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* Left = malloc(n1 * sizeof(int));
    int* Right = malloc(n2 * sizeof(int));

    printf("Left part:");
    for (int i = 0; i < n1; i++){
        Left[i] = array[left + i];
        printf(" %d", Left[i]);
    }
    printf("\n");

    printf("Right part:");
    for (int j = 0; j < n2; j++){
        Right[j] = array[mid + 1 + j];
        printf(" %d", Right[j]);
    }
    printf("\n");

    int l = 0;
    int r = 0;
    int i = left;

    while (l < n1 && r < n2) {
        if (Left[l] <= Right[r]) {
            array[i] = Left[l];
            l++;
        }
        else {
            array[i] = Right[r];
            r++;
        }
        i++;
    }

    while (l < n1) {
        array[i] = Left[l];
        l++;
        i++;
    }

    while (r < n2) {
        array[i] = Right[r];
        r++;
        i++;
    }

    printf("Merged parts:");
    for(int k = left; k <= right; k++){
        printf(" %d", array[k]);
    }
    printf("\n\n");

    free(Left);
    free(Right);
}

void merge_sort(int array[], int left, int right)
{
    if (left < right) {
        int mid = left - 1 + (right - left + 1) / 2;

        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);

        merge(array, left, mid, right);
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
    printf("\n\n");

    merge_sort(array, 0, n-1); 

    return 0;
}