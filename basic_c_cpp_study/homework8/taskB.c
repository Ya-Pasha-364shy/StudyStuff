#include <stdio.h>

#include <stdlib.h>

#include <stdint.h>

#include <stdbool.h>

#define ui unsigned int

/**
 * Description:
 *
 * На вход подается число n - число точек, и n строк, каждая из которых содержит два числа,
 * представляющие собой целочисленные координаты точки на координатной плоскости.
 * Цена соединения двух точек (xi, yi) и (xj, yj)  - манхэттенское расстояние между ними (|xi-xj| + |yi-yj|).
 * Выведите минимальную цены соединения всех точек.
 *
 * Все точки считаются соединенными, если существует единственный простой путь, соединяющий две любые точки.
 */

struct coordinates_list {
    bool visited;
    int x, y;
    ui cost;

    struct coordinates_list* next;
} __attribute__((aligned(4)));

typedef struct coordinates_list* coordinates_list_item;

#define FOREACH_ITEM_SAFE(cur, next) \
    for (coordinates_list_item item = cur; item; item = next)

static inline int manhattan_distance_bw_dots(int xi, int xj, int yi, int yj)
{
    return abs(xi - xj) + abs(yi - yj);
}

static inline int min(ui a, ui b)
{
    return a - b > 0 ? b : a;
}

int main(void)
{
    ui n = 0, x = 0, y = 0, sum = 0;
    int cx = 0, cy = 0;

    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    coordinates_list_item list_root_item = NULL;
    coordinates_list_item prev_item, next_item = NULL;
    coordinates_list_item current_item = NULL;

    for (ui i = 0; i < n; i++) {
        if (scanf("%u %u", &x, &y) != 2) {
            goto clean;
        }

        current_item = calloc(1, sizeof(coordinates_list_item));
        if (!current_item) {
            goto clean;
        }

        current_item->x = x;
        current_item->y = y;
        current_item->next = NULL;
        if (!i) {
            cx = x;
            cy = y;
            current_item->cost = 0;
            current_item->visited = true;
        } else {
            current_item->cost = manhattan_distance_bw_dots(cx, x, cy, y);
            current_item->visited = false;
        }

        if (list_root_item == NULL) {
            list_root_item = current_item;
        } else {
            prev_item->next = current_item;
        }
        prev_item = current_item;
    }

    while (true) {
        // выбираем ближайшую по цене точку
        ui min_cost = UINT32_MAX;
        coordinates_list_item choised = NULL;

        next_item = NULL;
        FOREACH_ITEM_SAFE(list_root_item, next_item)
        {
            if (item->visited == false && item->cost < min_cost) {
                choised = item;
                min_cost = item->cost;
            }
            next_item = item->next;
        }

        // все точки обойдены
        if (!choised) {
            break;
        } else {
            sum += choised->cost;
            choised->visited = true;
            // обновляем стоимости всех непосещённых точек, если необходимо
            next_item = NULL;
            FOREACH_ITEM_SAFE(list_root_item, next_item)
            {
                ui _min = min(item->cost, manhattan_distance_bw_dots(choised->x, item->x, choised->y, item->y));
                if (item->visited == false && _min < item->cost) {
                    item->cost = _min;
                }

                next_item = item->next;
            }
        }
    }
    printf("%u\n", sum);

clean:
    FOREACH_ITEM_SAFE(list_root_item, next_item)
    {
        next_item = item->next;
        free(item);
    }

    return EXIT_SUCCESS;
}