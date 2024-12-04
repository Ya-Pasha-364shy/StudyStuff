#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Description:
 *
 * На вход подается целое число n - количество вершин в ориентированном графе,
 * целое число m - количество ребер в графе, и далее подаются m строк
 * из двух целых чисел формата "a b",
 * где a - узел, откуда исходит ребро,
 * b - узел, куда направлено ребро (вершины в графе пронумерованы от 1 до n).
 * Необходимо найти такой узел (и вывести его номер), в который направлены ребра,
 * исходящие из всех других узлов, но из которого при этом не исходит ни одного ребра.
 * Если такого узла не существует, то необходимо вывести -1.
 */

bool has_out(bool** nd_row, size_t nodes, size_t node_id)
{
    for (size_t i = 0; i < nodes; ++i) {
        if (nd_row[node_id][i])
            return true;
    }
    return false;
}

bool is_alldom(bool** nd_row, size_t nodes, size_t node_id)
{
    for (size_t i = 0; i < nodes; ++i) {
        if (i != node_id && !nd_row[i][node_id])
            return false;
    }
    return true;
}

int main(void)
{
    size_t nodes, edges;
    if (scanf("%lu %lu", &nodes, &edges) != 2) {
        exit(EXIT_FAILURE);
    }

    bool* nd_tbl = calloc(nodes * nodes, sizeof(bool));
    bool** nd_row = calloc(nodes, sizeof(bool*));

    // заполняем массив указателей указателями на каждую i-строку
    for (size_t i = 0; i < nodes; ++i) {
        nd_row[i] = &nd_tbl[i * nodes];
    }

    for (size_t i = 0; i < edges; ++i) {
        unsigned src, dst;
        if (scanf("%u %u", &src, &dst) != 2) {
            exit(EXIT_FAILURE);
        }
        nd_row[src - 1][dst - 1] = true;
    }

    int result = -1;
    for (size_t i = 0; i < nodes; ++i) {
        // проверяем, есть ли выходы из этого узла и если нет, то проверяем есльб ли хотя бы одна ссылка на этот узел,
        // чтобы убедиться, что он в графе
        if (!has_out(nd_row, nodes, i) && is_alldom(nd_row, nodes, i)) {
            result = i + 1;
            break;
        }
    }
    printf("%d\n", result);

    free(nd_tbl);
    free(nd_row);

    return 0;
}
