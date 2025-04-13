#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dsu_t{
    int* parent;
    int* rank;
    int max_val;
} DSU;

// === Con/de-structor ===

void init_dsu(DSU* dsu)
{
    dsu->max_val = 8;

    dsu->parent = (int*)calloc(dsu->max_val, sizeof(int));
    dsu->rank = (int*)calloc(dsu->max_val, sizeof(int));
}

void delete_dsu(DSU* dsu)
{
    free(dsu->parent);
    free(dsu->rank);

    dsu->max_val = 0;
    dsu->rank = NULL;
    dsu->parent = NULL;
}

// === Functions ===

int make_set(DSU* dsu, int value)
{
    if (value >= dsu->max_val) {
        int old_max = dsu->max_val;
        dsu->max_val = value;

        int* new_parent = (int*)calloc(dsu->max_val, sizeof(int));
        int* new_size = (int*)calloc(dsu->max_val, sizeof(int));
        
        memcpy(new_parent, dsu->parent, old_max);
        memcpy(new_size, dsu->rank, old_max);

        free(dsu->parent);
        free(dsu->rank);

        dsu->parent = new_parent;
        dsu->rank = new_size;
    }

    if (dsu->parent[value] != 0)
        return 1;

    dsu->parent[value] = value;
    dsu->rank[value] = 1;

    return 0;
}

int find_set(int* result, DSU* dsu, int value)
{
    if (dsu->parent[value] == 0)
        return 1;

    if (dsu->parent[value] == value) {
        *result = value;
        return 0;
    }

    int ret_val = find_set(result, dsu, dsu->parent[value]);

    dsu->parent[value] = *result;

    return ret_val;
}

int union_sets(DSU* dsu, int val_a, int val_b)
{
    int parent_a;
    int parent_b;

    int ret = 0;
    ret += find_set(&parent_a, dsu, val_a);
    ret += find_set(&parent_b, dsu, val_b);

    if (ret != 0)
        return ret;

    int* parent = dsu->parent;
    int* rank = dsu->rank;

    if (parent_a != parent_b) {
        if (rank[parent_a] < rank[parent_b]) {
            int temp = parent_a;
            parent_a = parent_b;
            parent_b = temp;
        }

        parent[parent_b] = parent_a;

        if (rank[parent_a] == rank[parent_b])
            ++rank[parent_a];

        return 0;
    }

    else
        return 3;
}

// === Main ===

int main()
{
    DSU dsu;
    DSU* p_dsu = &dsu;

    init_dsu(p_dsu);

    printf("Make sets 1 2 3 4\n");

    make_set(p_dsu, 1);
    make_set(p_dsu, 2);
    make_set(p_dsu, 3);
    make_set(p_dsu, 4);

    int result;

    find_set(&result, p_dsu, 1);

    printf("Find set 1, result %d\n", result);

    find_set(&result, p_dsu, 2);

    printf("Find set 2, result %d\n", result);

    printf("Union sets 1 and 2\n");

    union_sets(p_dsu, 1, 2);

    find_set(&result, p_dsu, 1);

    printf("Find set 1, result %d\n", result);

    find_set(&result, p_dsu, 2);

    printf("Find set 2, result %d\n", result);

    delete_dsu(p_dsu);
}