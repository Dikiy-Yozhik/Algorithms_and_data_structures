#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 30 

void counting_sort(char array[][MAX_DIGITS], long long int n, long long int digit) { 
    int digits[16] = {0}; 
    char sortArr[n][MAX_DIGITS]; 

    // Подсчет количества элементов для каждой "цифры" в шестнадцатеричной системе
    for (long long int i = 0; i < n; i++) { 
        int index = (unsigned long long int)strtoull(array[i], NULL, 16) / digit % 16; 
        digits[index]++;
    } 

    // Обновление массива подсчета для получения индексного массива
    for (int i = 1; i < 16; i++) { 
        digits[i] += digits[i - 1]; 
    } 

    // Сортировка элементов по текущему разряду
    for (long long int i = n - 1; i >= 0; i--) { 
        int index = (unsigned long long int)strtoull(array[i], NULL, 16) / digit % 16; 
        strcpy(sortArr[--digits[index]], array[i]);  // Уменьшаем значение сразу
    } 

    // Копирование отсортированных элементов обратно в основной массив
    memcpy(array, sortArr, n * MAX_DIGITS); // Используем memcpy для быстрого копирования
} 

void radix_sort(char array[][MAX_DIGITS], long long int n) { 
    unsigned long long int max_el = 0; 

    // Нахождение максимального элемента
    for (long long int i = 0; i < n; i++) { 
        unsigned long long int value = (unsigned long long int)strtoull(array[i], NULL, 16); 
        if (value > max_el) { 
            max_el = value; 
        } 
    } 

    long long int digit = 1; 

    // Сортировка по каждому разряду
    while (max_el / digit > 0) { 
        printf("Sorting by digit for %llu:\n", digit); 
        counting_sort(array, n, digit); 
        printf("\n"); 
        digit *= 16; 
    } 
} 

int main() { 
    long long int n; 
    scanf("%lld", &n); 

    char array[n][MAX_DIGITS]; 
    for (long long int i = 0; i < n; i++) { 
        scanf("%s", array[i]); 
    } 

    radix_sort(array, n); 

    return 0; 
}
