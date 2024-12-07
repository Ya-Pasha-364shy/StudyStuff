#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

#include <stdbool.h>

/**
 * Description:
 *
 * Имеется неориентированный граф с n вершинами, каждая из которых пронумерована числами от 0 до n-1.
 * Каждая пара вершин соединена не более чем одним ребром, петель в графе также нет.
 * Необходимо определить, существует ли в графе путь, соединяющий две вершины с заданными индексами.
 * В случае, если такой путь существует (хотя бы один) выведите true, иначе - false.
 * При решении задачи ЗАПРЕЩАЕТСЯ использовать рекурсию.
 *
 * На вход подается число n (количество вершин в графе), m (число ребер в графе),
 * s (индекс вершины - начала пути), d (индекс вершины - конца пути) и m строк,
 * в каждой из которых содержатся индексы начала и конца одного из ребер графа.
 */

#define SCAN_INT(var)                                               \
    do {                                                            \
        int ret;                                                    \
        if ((ret = scanf("%d", &var)) != 1) {                       \
            printf("failed to read " #var " with code: %d\n", ret); \
            return -1;                                              \
        }                                                           \
    } while (0);

// список вершин от рассматриваемой вершины
typedef struct EdgeList {
    int node;
    struct EdgeList* next;
} EdgeList;

// спиисок связанных списков вершин
typedef struct {
    EdgeList** edges;
    int nodesCount;
    int isAllocated;
} Graph;

void graphClear(const Graph* graph)
{
    for (int i = 0; i < graph->nodesCount; i++) {
        if (graph->edges[i] == NULL) {
            continue;
        }
        EdgeList* list = graph->edges[i]->next;
        while (list != NULL) {
            EdgeList* tmp = list;
            list = tmp->next;
            free(tmp);
        }
        free(graph->edges[i]); // list's root
    }
    free(graph->edges);
}

// по индексу в списке получаем вложенный список,
// в котором хранится множество вершин, до которых у нас есть путь
// от текущей вершины, закодированной индексом внешнего списка.
bool graphAddEdge(Graph* graph, int nodeFrom, int nodeTo)
{
    if (graph->edges[nodeFrom] == NULL) {
        graph->edges[nodeFrom] = malloc(sizeof(EdgeList));
        if (!graph->edges[nodeFrom]) {
            goto clear;
        }
        graph->edges[nodeFrom]->next = NULL;
        graph->edges[nodeFrom]->node = nodeTo;
        return true;
    }

    EdgeList* list = graph->edges[nodeFrom];
    while (list->next != NULL) {
        // перемещаем указатель на последний элемент,
        // чтобы выделить под него память и проинициализировать.
        list = list->next;
    }

    list->next = malloc(sizeof(EdgeList));
    if (!list->next) {
        goto clear;
    }
    list->next->node = nodeTo;
    list->next->next = NULL;

    return true;

clear:
    graphClear(graph);
    return false;
}

bool graphHasEdge(Graph* graph, int nodeFrom, int nodeTo)
{
    EdgeList* list = graph->edges[nodeFrom];
    while (list != NULL) {
        if (list->node == nodeTo) {
            return true;
        }
        list = list->next;
    }
    return false;
}

bool graphIsPathExists(Graph* graph, int nodeFrom, int nodeTo)
{
    int queuePopIdx = 0;
    int queueAddIdx = 0;

    bool* visited = malloc(graph->nodesCount * sizeof(bool));
    int* queue = malloc(graph->nodesCount * sizeof(int));

    for (int i = 0; i < graph->nodesCount; i++) {
        visited[i] = false;
    }

    queue[queueAddIdx++] = nodeFrom;
    visited[nodeFrom] = true;

    while (queuePopIdx < queueAddIdx) {
        int currNode = queue[queuePopIdx++];

        if (currNode == nodeTo) {
            free(visited);
            free(queue);
            return true;
        }

        // bfs
        for (int i = 0; i < graph->nodesCount; i++) {
            if (graphHasEdge(graph, currNode, i)) {
                if (visited[i] == false) {
                    queue[queueAddIdx++] = i;
                    visited[i] = true;
                }
            }
        }
    }

    free(visited);
    free(queue);

    return false;
}

void graphInit(Graph* graph, int nodesCount)
{
    graph->edges = malloc(nodesCount * sizeof(EdgeList*));
    graph->nodesCount = nodesCount;

    for (int i = 0; i < graph->nodesCount; i++) {
        graph->edges[i] = NULL;
    }
}

int main()
{
    int n, m, s, d;
    SCAN_INT(n);
    SCAN_INT(m);
    SCAN_INT(s);
    SCAN_INT(d);

    Graph graph;
    graphInit(&graph, n);

    for (int i = 0; i < m; i++) {
        int node1, node2;
        SCAN_INT(node1);
        SCAN_INT(node2);
        if (!graphAddEdge(&graph, node1, node2) || !graphAddEdge(&graph, node2, node1)) {
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", graphIsPathExists(&graph, s, d) ? "true" : "false");

    graphClear(&graph);

    return EXIT_SUCCESS;
}