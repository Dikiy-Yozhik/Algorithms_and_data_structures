#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1000

typedef struct node_t{
    char str[11];
    struct node_t* next;
    struct node_t* prev;
}Node;

typedef struct{
    Node* head;
    Node* tail;
}List;

typedef struct Hash_node_t{
    char key[11];
    Node* node;
    struct Hash_node_t* next;
}Hash_node;

typedef struct{
    Hash_node** table;
}Hash_Table;

void init_Table(Hash_Table* hashTable){
    hashTable->table = malloc(HASH_SIZE * sizeof(Hash_node*));
    for(int i = 0; i < HASH_SIZE; i++){
        hashTable->table[i] = NULL;
    }
}

int hash_function(const char* str){
    int hash = 0;
    for(int i = 0; i < strlen(str); i++){
        hash += str[i];
    }
    return hash % HASH_SIZE;
}

void add_to_Hash(Hash_Table* hash_table, Node* node){
    int index = hash_function(node->str);
    Hash_node* new_node = malloc(sizeof(Hash_node));

    strcpy(new_node->key, node->str);
    new_node->node = node;
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

Node* find_in_Hash(Hash_Table* hash_table, const char* str){
    int index = hash_function(str);
    Hash_node* temp = hash_table->table[index];
    while(temp){
        if (strcmp(temp->key, str) == 0){
            return temp->node;
        }
        temp = temp->next;
    }
    return NULL;
}

void delete_from_Hash(Hash_Table* hash_table, const char* str){
    int index = hash_function(str);
    Hash_node* prev = NULL;
    Hash_node* temp = hash_table->table[index];
    while(temp){
        if(strcmp(temp->key, str) == 0){
            if(prev){
                prev->next = temp->next;
            } 
            else{
                hash_table->table[index] = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void add_node(List* list, char* str, Hash_Table* hash_table){
    Node* new_node = malloc(sizeof(Node));
    strcpy(new_node->str, str);
    new_node->next = NULL;
    new_node->prev = NULL;

    if(list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    
    add_to_Hash(hash_table, new_node);
}

Node* find_node(List* list, char* str, Hash_Table* hashTable){
    return find_in_Hash(hashTable, str);
}

void delete_node(List* list, char* str, Hash_Table* hash_table){
    Node* temp = find_node(list, str, hash_table);
    if(temp == list->head){
        list->head = temp->next;
    }
    else if(temp->next == NULL){
        list->tail = temp->prev;
        temp->prev->next = NULL;
    }
    else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    delete_from_Hash(hash_table, str);
    free(temp);
}

void print_next(List* list, char* str, Hash_Table* hash_table){
    Node* temp = find_node(list, str, hash_table)->next;

    if(temp == NULL){
        printf("-1\n");
    }
    else{
        printf("%s\n", temp->str);
    }
}

void free_Hash(Hash_Table* hash_table){
    for(int i = 0; i < HASH_SIZE; i++){
        Hash_node* temp = hash_table->table[i];
        while(temp){
            Hash_node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(hash_table->table);
}

void free_List(List* list){
    Node* temp = list->head;
    while(temp){
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
}

int main(){
    long long int n, q;
    scanf("%lld %lld", &n, &q);

    List list = {NULL, NULL};
    Hash_Table hash_table;
    init_Table(&hash_table);

    for(long long int i = 0; i < n; i++){
        char str[11];
        scanf("%s", str);
        add_node(&list, str, &hash_table);
    }

    for(long long int i = 0; i < q; i++){
        int oper;
        char str[11];
        scanf("%d %s", &oper, str);

        if(oper == 1){
            delete_node(&list, str, &hash_table);
        }
        else if(oper == 2){
            print_next(&list, str, &hash_table);
        }
    }

    free_List(&list);
    free_Hash(&hash_table);

    return 0;
}
