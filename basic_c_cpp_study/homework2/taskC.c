#include <stdio.h>

#include <limits.h>

/**
 * Описание:
 *
 * В первой строке на вход подается число n - длина последовательности.
 * Во второй строке - последовательность nums целых чисел длины n.
 * Найдите три числа из этой последовательности,
 * которые дают максимальное произведение, и выведите это максимальное произведение.
 * Решите задачу за линейное время O(n).
 */

int main()
{
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int num;
        if (scanf("%d", &num) != 1) {
            return 1;
        }

        if (num > max1) {
            max3 = max2;
            max2 = max1;
            max1 = num;
        } else if (num > max2) {
            max3 = max2;
            max2 = num;
        } else if (num > max3) {
            max3 = num;
        }

        if (num < min1) {
            min2 = min1;
            min1 = num;
        } else if (num < min2) {
            min2 = num;
        }
    }

    int p1 = max1 * max2 * max3;
    int p2 = max1 * min1 * min2;
    printf("%d\n", p1 > p2 ? p1 : p2);

    return 0;
}
