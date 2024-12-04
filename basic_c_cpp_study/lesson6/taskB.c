#include "stdio.h"
#include "stdlib.h"

/**
 * Description:
 *
 * На вход подаются целые числа m и n,
 * где m - число строк, а n - число столбцов.
 *
 * Далее подаются m строк, каждая из которых состоит из n нулей и единиц,
 * разделенных пробелами.
 * Из этих строк можно сконструировать карту (матрицу),
 * в которой 1 представляет сушу, а 0 - море
 * (предполагаем, что вне матрицы находится только море).
 * Остров - это суша, окруженная водой
 * (считаем, что два фрагмента суши соединены друг с другом,
 * если они смежны по горизонтали или по вертикали, но не по диагонали).
 * Необходимо найти и вывести число островов.
 *
 * Ограничения:
 * 1 <= m, n <= 300
 */

#define us unsigned short

int is_valid(int x, int y, int rows, int cols, us* surface, int* visited)
{
    return x >= 0 && x < rows && y >= 0 && y < cols && surface[x * cols + y] == 1 && !visited[x * cols + y];
}

void dfs(int x, int y, int rows, int cols, us* surface, int* visited)
{
    visited[x * cols + y] = 1;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (is_valid(nx, ny, rows, cols, surface, visited)) {
            dfs(nx, ny, rows, cols, surface, visited);
        }
    }
}

void ostrova(void)
{
    size_t rows, cols;
    if (scanf("%lu %lu", &rows, &cols) != 2)
        exit(EXIT_FAILURE);

    us* map = (us*)calloc(rows * cols, sizeof(us));
    if (!map) {
        exit(EXIT_FAILURE);
    }
    for (us i = 0; i < rows * cols; ++i) {
        if (scanf("%hu", &map[i]) != 1) {
            exit(EXIT_FAILURE);
        }
    }

    int* visited = (int*)calloc(rows * cols, sizeof(int));
    if (!visited) {
        exit(EXIT_FAILURE);
    }

    size_t res = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (map[i * cols + j] == 1 && !visited[i * cols + j]) {
                res++;
                dfs(i, j, rows, cols, map, visited);
            }
        }
    }
    free(map);
    free(visited);

    printf("%lu\n", res);
}

int main(void)
{
    ostrova();
    return EXIT_FAILURE;
}
