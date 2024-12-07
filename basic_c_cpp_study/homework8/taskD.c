#include <stdio.h>

#include <stdlib.h>

/**
 * Дана матрица размером m x n, в которой 0 обозначает пустое пространство,
 * а 1 - стены. Также даны координаты (x, y) - вашего текущего месторасположения,
 * где x - номер соответствующего ряда,
 * а y - соответствующей колонки в матрице.
 *
 * За один ход, вы можете передвинуться вверх, вниз, влево или вправо.
 * Вы не можете передвинуться в ячейку со стеной, или за пределы лабиринта.
 * Ваша задача - найти ближайший (достижимый за наименьшее число ходов) от вашего местоположения выход из матрицы.
 * Выход - это пустая ячейка на границе матрицы (ваше начальное местоположение не может быть выходом!).
 * Выведите число ходов, за которое можно добраться до ближайшего от вас выхода (или -1, если это невозможно).
 * На вход подаются числа m, n, x, y и m строк,
 * в каждой из которых находится n чисел (нулей или единиц), разделенных пробелами.
 */

typedef struct {
    int x, y, dist;
} ItemQueue;

#define int16_t short

int drs[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

int findPath(int** labii, int16_t m, int16_t n, int startX, int startY)
{
    int isValid(int i, int j)
    {
        return i >= 0 && j >= 0 && i < m && j < n && labii[i][j] == 0;
    }

    int16_t front = 0;
    int16_t back = 0;

    ItemQueue q[m * n];
    q[back++] = (ItemQueue) { startX, startY, 0 };

    int steps[m][n];
    for (int16_t i = 0; i < m; i++) {
        for (int16_t j = 0; j < n; j++) {
            steps[i][j] = -1;
        }
    }

    steps[startX][startY] = 0;

    while (front < back) {
        ItemQueue cur = q[front++];
        int curX = cur.x, curY = cur.y, curDist = cur.dist;
        if ((curX == 0 || curX == m - 1 || curY == 0 || curY == n - 1) && !(curX == startX && curY == startY)) {
            return curDist;
        }

        for (int16_t i = 0; i < 4; i++) {
            int newX = curX + drs[i][0];
            int newY = curY + drs[i][1];
            if (isValid(newX, newY) && steps[newX][newY] < 0) {
                steps[newX][newY] = curDist + 1;
                q[back++] = (ItemQueue) { newX, newY, curDist + 1 };
            }
        }
    }

    return -1;
}

int main(void)
{
    int16_t m, n, x, y;
    int rc = EXIT_SUCCESS;

    if (scanf("%hd %hd %hd %hd", &m, &n, &x, &y) != 4) {
        return EXIT_FAILURE;
    }

    int** labii = (int**)malloc(m * sizeof(int*));

    for (int16_t i = 0; i < m; i++) {
        labii[i] = (int*)malloc(n * sizeof(int));
    }
    for (int16_t i = 0; i < m; i++) {
        for (int16_t j = 0; j < n; j++) {

            if (scanf("%d", &labii[i][j]) != 1) {
                rc = EXIT_FAILURE;
                goto free_and_exit;
            }
        }
    }
    printf("%d\n", findPath(labii, m, n, x, y));

free_and_exit:
    for (int16_t i = 0; i < m; i++) {
        free(labii[i]);
    }
    free(labii);

    return rc;
}
