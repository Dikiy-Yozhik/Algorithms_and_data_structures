#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node_t{
    char* key;
    int value;
    bool state;
}node;

typedef struct hash_table_t{
    double rehash_size;
    int size;              // активные ноды
    int buffer_size;       // размер массива
    int non_ptr_size;      // все ноды
    node** arr;
}hash_table;

// конструктор - деструктор

node** new_nodes_arr(int buffer_size)
{
    node** ptr = malloc(buffer_size * sizeof(node*));

    for(int i = 0; i < buffer_size; i++){
        ptr[i] = NULL;
    }
    return ptr;
}

void new_table(hash_table* table)
{
    table -> size = 0;
    table -> non_ptr_size = 0;
    table -> rehash_size = 0.75;
    table -> buffer_size = 8;

    table -> arr = new_nodes_arr(table->buffer_size);
}

void delete_table(hash_table* table)
{
    node** arr = table->arr;

    for(int i = 0; i < table->buffer_size; i++){
        if(arr[i]){
            if(arr[i]->key && arr[i]->state){
                free(arr[i]->key);
            }
            free(arr[i]);
        }
    }
    free(arr);
}

// хэширование

int hash_Horner(char* string, int table_size, int key)
{
    int hash_result = 0;
    for(int i = 0; i != strlen(string); i++){
        hash_result = (key*hash_result + string[i]) % table_size;
    }
    hash_result = (hash_result*2 + 1) % table_size;

    return hash_result;
}

#define HASH_1(string, table_size) hash_Horner(string, table_size, table_size-1);
#define HASH_2(string, table_size) hash_Horner(string, table_size, table_size+1);


// создание нод

void update_node(node* node, char* key, int var)
{
    node -> key = malloc(sizeof(char) * (strlen(key)+1));
    memcpy(node->key, key, strlen(key));
    node->key[strlen(key)] = '\0';
    
    node -> value = var;
    node -> state = true;
}

bool _add(hash_table* table, char* key, int var)
{
    int h1 = HASH_1(key, table->buffer_size);
    int h2 = HASH_2(key, table->buffer_size);

    int i = 0;
    bool find_1_deleted = false;
    int first_deleted = 0;
    node** arr = table->arr;

    while(arr[h1] != NULL && i < table->buffer_size)
    {
  //      if(strcmp(arr[h1]->key, key) == 0 && arr[h1]->state)   в учебном коде это есть, но так одинаковые строки не будут попадать в таблицу
       //     return false;

        if(!arr[h1]->state && find_1_deleted == false){
            first_deleted = h1;
            find_1_deleted = true;
        }

        h1 = (h1 + h2) % table->buffer_size;
        i++;
    }

    if(find_1_deleted == false){
        node* new_node = malloc(sizeof(node));
        update_node(new_node, key, var);
        arr[h1] = new_node;
        table->non_ptr_size++;
    }
    else update_node(arr[first_deleted], key, var);

    table->size++;
    return true;
}

// resize и rehash

void resize(hash_table* table)
{
    int past_size = table->buffer_size;
    table->buffer_size *= 2;
    table->non_ptr_size = 0;
    table->size = 0;

    node** old_arr = table -> arr;
    table->arr = new_nodes_arr(table -> buffer_size);

    for(int i =0; i < past_size; i++){
        if(old_arr[i]){
            if(old_arr[i] -> state){
                _add(table, old_arr[i]->key, old_arr[i]->value);
                free(old_arr[i]->key);
                free(old_arr[i]);
            }
            else free(old_arr[i]);
        }
    }

    free(old_arr);
}

void rehash(hash_table* table)
{
    table->non_ptr_size = 0;
    table->size = 0;

    node** old_arr = table -> arr;
    table->arr = new_nodes_arr(table -> buffer_size);

    for(int i =0; i < table->buffer_size; i++){
        if(old_arr[i]){
            if(old_arr[i] -> state){
                _add(table, old_arr[i]->key, old_arr[i]->value);
                free(old_arr[i]->key);
                free(old_arr[i]);
            }
            else free(old_arr[i]);
        }
    }

    free(old_arr);    
}

// ....

bool add(hash_table* table, char* key, int var)
{
    if(table->size + 1 > (table->rehash_size * table->buffer_size)){
        resize(table);
    }
    else if(table->non_ptr_size > 2 * table->size){
        rehash(table);
    }

    return _add(table, key, var);
}

// удаление нод

bool delete_node(hash_table* table, char* key)
{
    int h1 = HASH_1(key, table->buffer_size);
    int h2 = HASH_2(key, table->buffer_size);
    
    int i = 0;
    node** arr = table->arr;

    while(arr[h1] != NULL && i < table->buffer_size)
    {
        if(strcmp(arr[h1]->key, key) == 0 && arr[h1]->state){
            arr[h1] -> state = false;
            free(arr[h1]->key);
            table -> size--;

            return true;
        }

        h1 = (h1 + h2) % table->buffer_size;
        i++;
    }
    return false;
}

// поиск нод

bool find(hash_table* table, char* key, int* var)
{
    int h1 = HASH_1(key, table->buffer_size);
    int h2 = HASH_2(key, table->buffer_size);
    
    int i = 0;
    node** arr = table->arr;

    while(arr[h1] != NULL && i < table->buffer_size)
    {
        if(strcmp(arr[h1]->key, key) == 0 && arr[h1]->state){
            *var = arr[h1]->value;
            return true;
        }

        h1 = (h1 + h2) % table->buffer_size;
        i++;
    }
    return false;
}

void print_table(hash_table* table)
{
    node** arr = table->arr;
    for(int i = 0; i < table->buffer_size; i++){
        if(arr[i]){
            if(arr[i]->state){
                puts(arr[i]->key);
                printf("%d\n", arr[i]->value);
            }
            else puts("Deleted node");
        }
        else puts("---");
    }
    printf("\n");
}

int main()
{
    hash_table table;
    hash_table* p_table = &table;
    new_table(p_table);

    add(p_table, "boom", 14);
    add(p_table, "boom", 15);
    add(p_table, "foxy", 16);
    add(p_table, "roof", 17);

    delete_node(p_table, "roof");

    print_table(p_table);

    delete_table(p_table);
    
    return 0;
}