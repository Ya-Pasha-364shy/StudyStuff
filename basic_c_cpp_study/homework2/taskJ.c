#include <stdio.h>

#include <stdlib.h>

typedef long unsigned int lui;

/**
 * Описание:
 *
 * На вход подается два числа n, k.
 * Выведите C(n, k) - число сочетаний из n по k
 */

lui factorial(lui n)
{
    lui factorial = 1;

    while (n > 1) {
        factorial *= n--;
    }

    return factorial;
}

int main()
{
    lui n, k;
    if (scanf("%lu %lu", &n, &k) != 2) {
        return EXIT_FAILURE;
    }

    lui result = factorial(n) / (factorial(n - k) * factorial(k));

    printf("%lu\n", result);
    return EXIT_SUCCESS;
}