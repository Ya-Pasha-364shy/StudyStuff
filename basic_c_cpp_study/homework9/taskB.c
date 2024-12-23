#include <math.h>

#include <stdio.h>

#include <stdbool.h>

/**
 * Description:
 *
 * Методом Ньютона найдите корень уравнения sin(x)-1/x=0
 * (единственный) на заданном промежутке.
 * Ответ выведите с точностью до четырех знаков после запятой
 * (в формате 0.xxxx, округленное по правилам математического округления:
 * вместо 0.11115 выводим 0.1112
 * На вход подаются числа a и b (типа double) - начало и конец отрезка, на котором ищем корень
 *
 * Ограничения:
 * a и b - типа double
 * ответ выводится в формате 0.xxxx (округляем по правилам математического округления)
 * При решении задачи запрещается использовать точную формулу для производной (вычисляйте ее численно)
 */

#define SCAN_DOUBLE(var)                                            \
    do {                                                            \
        int ret;                                                    \
        if ((ret = scanf("%lf", &var)) != 1) {                      \
            printf("failed to read " #var " with code: %d\n", ret); \
            return -1;                                              \
        }                                                           \
    } while (0);

// исходная функция от х
double F(double x)
{
    return sin(x) - 1 / x;
}

// первая производная от функции F
double F_1(double x)
{
    return cos(x) + 1 / pow(x, 2);
}

int main()
{
    const double epsilon = 1e-6;
    double start = 0, end = 0, next = 0;

    SCAN_DOUBLE(start);
    SCAN_DOUBLE(end);

    double mid = (start + end) / 2.0;

    while (1) {
        double Fx = F(mid);
        double Fx_1 = F_1(mid);

        if (fabs(Fx_1) < epsilon) {
            printf("no root\n");
            return 0;
        }

        next = mid - Fx / Fx_1;

        // достаточное приближение
        if (fabs(next - mid) < epsilon) {
            mid = next;
            break;
        } else {
            mid = next;
        }
    }

    if (start < mid && mid > end) {
        printf("no root\n");
    } else {
        printf("%.4f\n", mid);
    }

    return 0;
}