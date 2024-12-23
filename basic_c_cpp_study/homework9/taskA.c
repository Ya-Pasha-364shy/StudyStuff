#include <math.h>

#include <stdio.h>

#include <stdbool.h>

/**
 * Description:
 *
 * Методом простой итерации найдите корень уравнения
 * `4⋅(1+√(x))⋅ln(x)−1=0` (единственный) на заданном промежутке.
 * Ответ выведите с точностью до четырех знаков после запятой (в формате 0.xxxx,
 * округляя математически: если ответ 0.12225, то выводим 0.1224).
 * Если корень не найден, или не входит в заданный промежуток
 * то выведите "no root".
 * На вход подаются числа a и b (типа double) - начало и конец отрезка,
 * на котором ищем корень
 *
 * Ограничения:
 * a и b - типа double
 * ответ выводится в формате 0.xxxx, с математическим округлением
 */

#define SCAN_DOUBLE(var)                                            \
    do {                                                            \
        int ret;                                                    \
        if ((ret = scanf("%lf", &var)) != 1) {                      \
            printf("failed to read " #var " with code: %d\n", ret); \
            return -1;                                              \
        }                                                           \
    } while (0);

double iteration(double x)
{
    /**
     * Выведим x из неизвестное из уравнения:
     * 1) 4 * (sqrt(x) + 1) * log(x) - 1 = 0
     * 2) 4 * (sqrt(x) + 1) * log(x) = 1
     * 3) (sqrt(x) + 1) * log(x) = 1 / 4
     * 4) log(x) = (1 / 4) / (sqrt(x) + 1)
     * 5) x = exp((1 / 4) / (sqrt(x) + 1))
     */
    return exp(1.0 / 4.0 / (sqrt(x) + 1.0));
}

int main()
{
    double epsilon = 1e-6;
    double start = 0, end = 0;

    SCAN_DOUBLE(start);
    SCAN_DOUBLE(end);

    double mid = (start + end) / 2.0;

    while (1) {
        double xNext = iteration(mid);

        if (fabs(xNext - mid) < epsilon) {
            mid = xNext;
            break;
        }

        mid = xNext;
    }

    if (mid < start || mid > end) {
        printf("no root\n");
    } else {
        printf("%.4f\n", mid);
    }

    return 0;
}