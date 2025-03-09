#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//for chars

typedef struct{
    char oper[1000];
    int len;
}Stack;

void init_stack(Stack* stack){
    stack->len = 0;
}

char peek(Stack* stack){
    return stack->oper[stack->len-1];
}

bool is_empty(Stack* stack){
    return stack->len == 0;
}

void push(Stack* stack, char a){
    stack->oper[stack->len] = a;
    stack->len++; 
}

char pop(Stack* stack){
    if(!is_empty(stack)){
        stack->len--;
        return stack->oper[stack->len];
    }
    return 0;
} 

//for all

bool is_digit(char a){
    return !(strchr("0123456789", a) == NULL);
}

int priority(char op){
    switch (op) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        default:
            return 0;
    }
}

//for values

typedef struct{
    int val[1000];
    int len;
}Stack_t;

void init_stack_t(Stack_t* stack){
    stack->len = 0;
}

bool is_empty_t(Stack_t* stack){
    return stack->len == 0;
}

int peek_t(Stack_t* stack){
    return stack->val[stack->len-1];
}

void push_t(Stack_t* stack, int a){
    stack->val[stack->len] = a;
    stack->len++; 
}

int pop_t(Stack_t* stack){
    if(!is_empty_t(stack)){
        stack->len--;
        return stack->val[stack->len];
    }
    return 0;
} 

//................

char* polish_notation(char* str){
    char* res = malloc(1500 * sizeof(char));
    Stack stack;
    init_stack(&stack);
    int i = 0, j = 0;

    while(str[i] != '\0'){
        if(is_digit(str[i])){
            while(str[i] != '\0' && is_digit(str[i])){
                res[j++] = str[i++];
            }
            res[j++] = ' ';
            continue;
        }
        if(str[i] == '('){
            push(&stack, str[i++]);
            continue;
        }
        if(str[i] == ')'){
            while(peek(&stack) != '('){
                res[j++] = pop(&stack);
                res[j++] = ' ';
            }
            pop(&stack);
            i++;
            continue;
        }
        while(!is_empty(&stack) && (peek(&stack) != '(') && (priority(str[i]) <= priority(peek(&stack)))){
            res[j++] = pop(&stack);
            res[j++] = ' ';
        }

        push(&stack, str[i++]);
    }

    while(!is_empty(&stack)){
        res[j++] = pop(&stack);
        res[j++] = ' ';
    }

    res[j] = '\0';
    return res;
}

int calculation(char* str){
    Stack_t stack;
    init_stack_t(&stack);

    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == ' '){
            i++;
            continue;
        }
        else if(is_digit(str[i])){
            int a = atoi(str+i);
            push_t(&stack, a);
            while(str[i] != ' ' && str[i] != '\0') i++;
        }
        else{
            int b = pop_t(&stack);
            int a = pop_t(&stack);
            switch(str[i]){
                case '+':
                    push_t(&stack, a + b);
                    break;
                case '-':
                    push_t(&stack, a - b);
                    break;
                case '*':
                    push_t(&stack, a * b);
                    break;
                case '/':
                    push_t(&stack, a / b);
                    break;
            }
            i++;
        }
    }
    return pop_t(&stack);
}

//...............

int main(){
    char str[1000];
    scanf("%s", str);

    printf("Expression:\n");
    printf("%s\n", str);

    char* res_str = polish_notation(str);
    printf("Reverse Polish Notation:\n");
    puts(res_str);

    int res = calculation(res_str);
    printf("Result:\n");
    printf("%d", res);

    return 0;
}