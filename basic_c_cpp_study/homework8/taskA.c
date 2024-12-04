#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ui unsigned int
#define MAX_SIZE 128

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

typedef struct {
    ui data[MAX_SIZE];
    ui front;
    ui tail;
    ui size;
} queue;

void initializeQueue(queue* q)
{
    q->front = 0;
    q->tail = -1;
    q->size = 0;
    memset(q->data, 0, sizeof(ui) * MAX_SIZE);
}

bool isEmpty(queue* q)
{
    return q->size == 0;
}

bool isFull(queue* q)
{
    return q->size == MAX_SIZE;
}

bool enqueue(queue* q, ui value)
{
    if (isFull(q)) {
        return false;
    }

    q->tail = (q->tail + 1) % MAX_SIZE;
    q->data[q->tail] = value;
    q->size++;

    return true;
}

ui dequeue(queue* q)
{
    ui top;

    top = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;

    return top;
}

int main(void)
{
    ui vertexs, edges, start_v, finish_v, i = 0;

    if (scanf("%u", &vertexs) != 1
        || scanf("%u", &edges) != 1
        || scanf("%u", &start_v) != 1
        || scanf("%u", &finish_v) != 1) {
        EXIT_FAILURE;
    }

    bool* table = calloc(vertexs * vertexs, sizeof(bool));
    bool** table_rows = calloc(vertexs, sizeof(bool*));
    for (; i < vertexs; ++i) {
        table_rows[i] = &table[i * vertexs];
    }

    for (i = 0; i < edges; ++i) {
        ui src, dst;
        if (scanf("%u %u", &src, &dst) != 2) {
            return EXIT_FAILURE;
        }

        table_rows[src][dst] = true;
    }

    bool path_exists = false;
    queue q;
    initializeQueue(&q);
    enqueue(&q, start_v);

    // bfs
    while (!isEmpty(&q) && !path_exists) {
        ui top = dequeue(&q);
        if (top == finish_v) {
            path_exists = true;
            break;
        }

        for (i = 0; i < vertexs; i++) {
            if (table_rows[top][i] == true) {
                if (false == enqueue(&q, i)) {
                    return -4;
                }
            }
        }
    }

    path_exists == true ? printf("true\n") : printf("false\n");

    free(table);
    free(table_rows);

    return EXIT_SUCCESS;
}