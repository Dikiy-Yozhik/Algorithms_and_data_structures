#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define STRING_LENGTH 16
#define P 1000000007

typedef unsigned long long ull;

typedef struct Node{
    char string[STRING_LENGTH];
    struct Node* next;
}Node;

unsigned long long hash_function(const char* str, Node** hash_table, int m){
    unsigned long long int h1 = 0;
    unsigned long long to_pow = 1;
    for(int i = 0; i < strlen(str); i++){
        h1 += str[i] * to_pow;
        to_pow *= 263;
        to_pow %= P;
    }
    h1 %= P;

    return h1%m;
}

Node* new_node(const char* str){
    Node* new_Node = malloc(sizeof(Node));
    strcpy(new_Node->string, str);
    new_Node->next = NULL;
    return new_Node;
}

void add_string(const char* str, Node** hash_table, int m){
    unsigned long long index = hash_function(str, hash_table, m);
    Node* current = hash_table[index];
    
    while (current != NULL){
        if (strcmp(current->string, str) == 0) {
            return; 
        }
        current = current->next;
    }
    
    Node* new_Node = new_node(str);
    new_Node->next = hash_table[index];
    hash_table[index] = new_Node;
}

void delete_string(const char* str, Node** hash_table, int m){
    unsigned long long index = hash_function(str, hash_table, m);
    Node* current = hash_table[index];
    Node* prev = NULL;

    while (current != NULL){
        if (strcmp(current->string, str) == 0){
            if (prev == NULL){
                hash_table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool find_string(const char* str, Node** hash_table, int m){
    unsigned long long index = hash_function(str, hash_table, m);
    Node* current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->string, str) == 0) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

void check_list(int index, Node** hash_table){
    Node* current = hash_table[index];
    
    if (current == NULL) {
        printf("\n");
        return;
    }
    int i = 0;
    while (current != NULL){
        if(i++ > 0) printf(" ");
        printf("%s", current->string);
        
        current = current->next;
    }
    
    printf("\n");
}

int main(){
    int m;
    scanf("%d", &m);
    
    Node** hash_table = malloc(m * sizeof(Node*));
    for (int i = 0; i < m; i++){
        hash_table[i] = NULL;
    }

    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++){
        char command[10], string[STRING_LENGTH];
        scanf("%s", command);
        
        if (strcmp(command, "add") == 0){
            scanf("%s", string);
            add_string(string, hash_table, m);
        } 
        else if (strcmp(command, "del") == 0){
            scanf("%s", string);
            delete_string(string, hash_table, m);
        } 
        else if (strcmp(command, "find") == 0){
            scanf("%s", string);
            printf(find_string(string, hash_table, m) ? "yes\n" : "no\n");
        } 
        else if (strcmp(command, "check") == 0){
            int index;
            scanf("%d", &index);
            check_list(index, hash_table);
        }
    }

    for (int i = 0; i < m; i++){
        Node* temp = hash_table[i];
        while (temp != NULL){
            Node* current = temp;
            temp = temp->next;
            free(current);
        }
    }
    
    free(hash_table);
    
    return 0;
}
