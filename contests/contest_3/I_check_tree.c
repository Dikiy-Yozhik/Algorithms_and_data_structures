#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct{
    long long int left;
    long long int right;
}Pair;

typedef struct{
    long long int* values;
    Pair* edges;
    long long int len;
}Tree;

bool check(Tree* tree, long long int i, long long int min, long long int max){
    if(i == -1){
        return true;
    }
    
    long long int* arr = tree->values;

    if(!(min <= arr[i] && arr[i] < max)){
        return false;
    }

    return (check(tree, tree->edges[i].left, min, arr[i]) && check(tree, tree->edges[i].right, arr[i], max));
}

int main(){
    long long int n;
    scanf("%lld", &n);

    long long int* nodes = malloc(n * sizeof(long long int));
    Pair* children = malloc(n * sizeof(Pair));

    for(long long int i = 0; i < n; i++){
        scanf("%lld %lld %lld", &nodes[i], &children[i].left, &children[i].right);
    }

    Tree tree = {nodes, children, n};

    if(check(&tree, 0, LLONG_MIN, LLONG_MAX)){
        printf("CORRECT");
    }
    else{
        printf("INCORRECT");
    }

    free(nodes);
    free(children);

    return 0;
}
