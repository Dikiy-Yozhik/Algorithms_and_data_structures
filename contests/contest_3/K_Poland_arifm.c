#include <stdio.h>

typedef struct{
    int* arr;
    int len;
}Stack;

int calculation(Stack* stack){
    while(stack->len > 1){
        int a = pop(stack)&0x0F;
        int b = pop(stack)&0x0F;
        char oper = pop(stack);
        switch(oper){
            case '+':
                push(stack, a + b);
                break;
            case '-':
                push(stack, a - b);
                break;
            case '*':
                push(stack, a * b);
                break;
            case '/':
                push(stack, a / b);
                break;
        }
    }
    
}

int main(){
    char str[1000];
    scanf("%s", str);

    printf("Expression:\n");
    printf("%s\n", str);

    Stack stack = {"+3+21", 5};

    polish_notation(str);
    char str1[] = "1 2 + 3 +";

    printf("Reverse Polish Notation:\n");
    printf("%s\n", str1);

    int res = calculation(&stack);

    return 0;
}