#include <stdio.h>

typedef unsigned int ui;

/**
 * Описание:
 *
 * Пусть "дополнение" целого числа - это число,
 * которое мы получим при замене всех 1 на 0 и всех 0 на 1
 * в бинарном представлении исходного числа.
 * Например, число 5 в бинарной системе счисления записывается как "101".
 * Значит, его дополнение - это число "010" (2 в десятичной).
 * На вход подается число n, выведите его дополнение
 * (в десятичной форме, как целое число).
 */

int main()
{
    ui number, inverse_number;
    if (scanf("%u", &number) != 1) {
        return -1;
    }
    if (!number) {
        printf("1\n");
        return 0;
    }

    ui mask = 1;
    while (number >= mask) {
        mask <<= 1;
    }
    inverse_number = (mask - 1) ^ number;
    printf("%u\n", inverse_number);

    return 0;
}