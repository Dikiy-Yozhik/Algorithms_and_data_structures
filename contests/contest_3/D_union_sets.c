#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* parent;
    int* rank;
    int max;
}dsu;

int max(int a, int b){
    return a<b ? b : a;
}

int find_set(dsu* join_set, int i){
    int* parent = join_set->parent;

    if(i == parent[i]-1)
        return parent[i];
    
    return find_set(join_set, parent[i]-1);
}

int union_sets(dsu* join_set, int i, int j){
    int* parent = join_set->parent;
    int* rank = join_set->rank;

    int parent_first = find_set(join_set, i);
    int parent_second = find_set(join_set, j);

    if(parent_first != parent_second)
    {
        if(rank[parent_first-1] < rank[parent_second-1]){
            int temp = parent_first;
            parent_first = parent_second;
            parent_second = temp;
        }

        parent[parent_second-1] = parent_first;
        rank[parent_first-1] += rank[parent_second-1];

        return rank[parent_first-1];
    }

    else{
        return rank[parent_first-1];
    }
}

int main(){
    int n, m, max_val = -1;
    scanf("%d %d", &n, &m);

    int* index = malloc(n * sizeof(int));
    int* depth = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        index[i] = i+1;
        scanf("%d", &depth[i]);
        if(depth[i] > max_val) max_val = depth[i];
    }

    dsu join_set = {index, depth, max_val};

    int i, j;
    for(int k = 0; k < m; k++){
        scanf("%d %d", &i, &j);
        max_val = max(max_val, union_sets(&join_set, i-1, j-1));
        printf("%d\n", max_val);
    }

    free(index);
    free(depth);

    return 0;
}