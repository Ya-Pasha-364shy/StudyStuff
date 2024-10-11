#include <stdio.h>

#include <stdlib.h>

typedef long unsigned int lui;

/**
 * Описание:
 *
 * На вход подаётся число n. Найдите его факториал
 */

int main()
{
    lui n;
    lui factorial = 1;

    if (scanf("%lu", &n) != 1) {
        return EXIT_FAILURE;
    }

    while (n > 1) {
        factorial *= n--;
    }

    printf("%lu\n", factorial);
    return EXIT_SUCCESS;
}