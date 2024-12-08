#include <stdio.h>

#include <limits.h>

#include <stdlib.h>

#include <stdbool.h>

/**
 * Дана сеть (ориентированный граф) из n вершин,
 * пронумерованных числами от 1 до n.
 * Каждому ребру (vi, vj) присвоен вес (целочисленный) - время,
 * за которое сигнал проходит из вершины vi в вершину vj.
 *
 * Пусть k - индекс вершины, из которой посылаем сигнал.
 * Выведите минимальное время, которое понадобится сигналу,
 * чтобы достичь всех остальных вершин в сети (если это невозможно, то выведите -1).
 *
 * На вход подается число n, число k, число m и m строк,
 * каждая из которых содержит индекс начала ребра, индекс конца ребра и вес ребра.
 *
 * Ограничения:
 * 1 <= k <= n <= 100
 * 1 <= m <= 6000
 * В графе нет петель и мультиребер (нескольких ребер, исходящих из vi в vj)
 * 0 <= wij <= 100, где wij - вес ребра из vi в vj
 */

#define SCAN_INT(var)                                               \
    do {                                                            \
        int ret;                                                    \
        if ((ret = scanf("%d", &var)) != 1) {                       \
            printf("failed to read " #var " with code: %d\n", ret); \
            return -1;                                              \
        }                                                           \
    } while (0);

typedef unsigned int ui;

// ==================================
// ============= GRAPH ==============
// ==================================

// список вершин от рассматриваемой вершины, закодированной индексом
typedef struct EdgeList {
    int node;
    int weigth;

    struct EdgeList* next;
} EdgeList;

// спиисок связанных списков вершин
typedef struct {
    EdgeList** edges;
    int nodesCount;
} Graph;

// ==================================
// ========== QUEUE ITEM ============
// ==================================

typedef struct Vertex {
    int node;
    int label;
} Vertex;

// ==================================

void graphClear(const Graph* graph)
{
    for (int i = 0; i < graph->nodesCount; i++) {
        EdgeList* list = graph->edges[i];

        while (list != NULL) {
            EdgeList* tmp = list;
            list = list->next;
            free(tmp); // Удаление элемента списка
        }
    }
    free(graph->edges); // Удаление массива указателей
}

// по индексу в списке получаем вложенный список,
// в котором хранится множество вершин, до которых у нас есть путь
// от текущей вершины, закодированной индексом внешнего списка.
bool graphAddEdge(Graph* graph, int nodeFrom, int nodeTo, int weigth)
{
    if (graph->edges[nodeFrom] == NULL) {
        graph->edges[nodeFrom] = malloc(sizeof(EdgeList));
        if (!graph->edges[nodeFrom]) {
            goto clear;
        }
        graph->edges[nodeFrom]->next = NULL;
        graph->edges[nodeFrom]->node = nodeTo;
        graph->edges[nodeFrom]->weigth = weigth;

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
    list->next->weigth = weigth;

    list->next->next = NULL;

    return true;

clear:
    graphClear(graph);
    return false;
}

int graphGetWeigthIfEdge(Graph* graph, int nodeFrom, int nodeTo)
{
    EdgeList* list = graph->edges[nodeFrom];
    while (list != NULL) {
        if (list->node == nodeTo) {
            return list->weigth;
        }
        list = list->next;
    }
    return INT_MIN;
}

int checkPing(Graph* graph, int nodeFrom)
{
    int maxWeigth = INT_MIN;

    int queueAddIdx = 0;
    int queuePopIdx = 0;

    // bool visited[graph->nodesCount];

    size_t queue_size = graph->nodesCount * 2;
    Vertex queue[queue_size];
    queue[queueAddIdx++] = (Vertex) { .node = nodeFrom, .label = 0 };

    int distances[graph->nodesCount];
    for (int i = 0; i < graph->nodesCount; i++) {
        // visited[i] = false;
        distances[i] = (i == nodeFrom) ? 0 : INT_MAX;
    }

    while (queueAddIdx > queuePopIdx) {
        Vertex currentV = queue[queuePopIdx++ % queue_size];

        if (currentV.label > distances[currentV.node]) {
            continue;
        }

        for (EdgeList* edge = graph->edges[currentV.node]; edge != NULL; edge = edge->next) {
            // if (visited[edge->node] == true) {
            //     continue;
            // }

            int new_cost = distances[currentV.node] + edge->weigth;
            if (new_cost < distances[edge->node]) {
                distances[edge->node] = new_cost;
                queue[queueAddIdx++ % queue_size] = (Vertex) { .node = edge->node, .label = new_cost };
            }
        }
        // visited[currentV.node] = true;
    }

    for (int i = 0; i < graph->nodesCount; i++) {
        if (distances[i] == INT_MAX) {
            maxWeigth = -1;
            break;
        }
        if (distances[i] > maxWeigth) {
            maxWeigth = distances[i];
        }
    }

    return maxWeigth;
}

void graphInit(Graph* graph, int nodesCount)
{
    graph->edges = malloc(nodesCount * sizeof(EdgeList*));
    graph->nodesCount = nodesCount;

    for (int i = 0; i < graph->nodesCount; i++) {
        graph->edges[i] = NULL;
    }
}

int main(void)
{
    int n, start, m;
    SCAN_INT(n);
    SCAN_INT(start);
    start -= 1;

    SCAN_INT(m);

    Graph graph;
    graphInit(&graph, n);
    n -= 1;

    for (int i = 0; i < m; i++) {
        int node1, node2, weigth;
        SCAN_INT(node1);
        node1 -= 1;
        SCAN_INT(node2);
        node2 -= 1;
        SCAN_INT(weigth);

        // ориентированный граф
        if (!graphAddEdge(&graph, node1, node2, weigth)) {
            return EXIT_FAILURE;
        }
    }

    printf("%d\n", checkPing(&graph, start));

    graphClear(&graph);

    return EXIT_SUCCESS;
}