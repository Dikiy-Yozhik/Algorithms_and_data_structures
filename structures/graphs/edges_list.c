#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge_t{
    int from;
    int to;
} edge;

typedef struct edge_list_t{
    edge** list;
    int len;
    int n_edges;
} Edge_List;

// === Con/de-structor ===

void init_list(Edge_List* list)
{
    list->len = 8;
    list->list = malloc(sizeof(edge*)*list->len);
    list->n_edges = 0;
}

void delete_list(Edge_List* list)
{
    for(int i = 0; i < list->n_edges; i++)
        free(list->list[i]);

    free(list->list);
}

// === Functions ===

void add_edge(Edge_List* list, int from, int to)
{
    if (list->n_edges+1 == list->len) {
        list->len = list->len*2;
        edge** new_list = malloc(sizeof(edge*)*list->len);
        memcpy(new_list, list->list, list->n_edges);
        delete_list(list);
        list->list = new_list;
    }

    list->list[list->n_edges] = malloc(sizeof(edge));
    list->list[list->n_edges]->from = from;
    list->list[list->n_edges]->to = to;

    list->n_edges++;
}

void print_list(Edge_List* list)
{
    for (int i = 0; i < list->n_edges; i++) {
        printf("%ld to %ld ", list->list[i]->from, list->list[i]->to);
        printf("\n");
    }
}

// === Main ===

int main()
{
    Edge_List l;
    Edge_List* p_l = &l;

    init_list(p_l);

    print_list(p_l);

    add_edge(p_l, 2, 3);
    add_edge(p_l, 3, 5);

    add_edge(p_l, 2, 6);
    add_edge(p_l, 6, 7);
    add_edge(p_l, 7, 5);

    print_list(p_l);

    delete_list(p_l);

    return 0;
}