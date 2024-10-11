#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

typedef unsigned short ui;

/**
 * Описание:
 *
 * На вход подается число n - длина последовательности,
 * и последовательность чисел nums, в которой ровно один
 * элемент встречается один раз, а все остальные элементы - по два раза.
 * Выведите элемент, который встретился один раз.
 * Алгоритм должен отрабатывать за линейное время (O(n)) и за константу по памяти.
 */

int main()
{
    ui N;
    int unique_number = 0, current_number;

    if (scanf("%hu", &N) != 1) {
        return EXIT_FAILURE;
    }
    for (ui i = 0; i < N; i++) {
        if (scanf("%d", &current_number) != 1) {
            return EXIT_FAILURE;
        }
        unique_number ^= current_number;
    }

    printf("%d\n", unique_number);
    return EXIT_SUCCESS;
}