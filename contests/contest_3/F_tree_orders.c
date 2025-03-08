#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int left;
    int right;
}Pair;

void in_order(int* arr, Pair* childs, int i){
    if(childs[i].left != -1){
        in_order(arr, childs, childs[i].left);
    }
    
    printf("%d ", arr[i]);

    if(childs[i].right != -1){
        in_order(arr, childs, childs[i].right);
    }
}

void pre_order(int* arr, Pair* childs, int i){
    printf("%d ", arr[i]);

    if(childs[i].left != -1){
        pre_order(arr, childs, childs[i].left);
    }

    if(childs[i].right != -1){
        pre_order(arr, childs, childs[i].right);
    }
}

void post_order(int* arr, Pair* childs, int i){
    if(childs[i].left != -1){
        post_order(arr, childs, childs[i].left);
    }
    
    if(childs[i].right != -1){
        post_order(arr, childs, childs[i].right);
    }
    
    printf("%d ", arr[i]);
}

int main(){
    int n;
    scanf("%d", &n);

    int* nodes = malloc(n * sizeof(int));
    Pair* children = malloc(n * sizeof(Pair));

    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &nodes[i], &children[i].left, &children[i].right);
    }

    in_order(nodes, children, 0);
    printf("\n");
    pre_order(nodes, children, 0);
    printf("\n");
    post_order(nodes, children, 0);

    return 0;
}