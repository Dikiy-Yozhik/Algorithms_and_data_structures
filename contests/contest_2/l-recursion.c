#include <stdio.h>
#include <math.h>

int l_recursion(int a, int b, int c){
    if(a <= 0 || b <= 0 || c <= 0){ 
        return 1;
    }
    else if(a > 20 || b > 20 || c > 20){
        return l_recursion(20, 20, 20);
    }
    else if(a > b && a > c){
        return l_recursion(a-1, b, c) + l_recursion(a-1, b-1, c) + l_recursion(a-1, b, c-1) - l_recursion(a-1, b-1, c-1);
    }
    else{
        return pow(2, a);
    }
}

int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int answer = l_recursion(a, b, c);
    printf("%d", answer);
    return 0;
}