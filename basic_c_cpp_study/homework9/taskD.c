#include <math.h>
#include <stdio.h>

/**
 * Description:
 *
 * Методом Ньютона найдите корень уравнения sin(x)-1/x=0 (единственный) на заданном промежутке.
 * Ответ выведите с точностью до четырех знаков после запятой
 * (в формате 0.xxxx, округленное по правилам математического округления - вместо 0.11115 выводим 0.1112).
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

// z = 3x^2 + xy + 2y^2 - x - 4y
// dz/dx = 6x + y - 1
double dz_dx(double x, double y)
{
    return 6 * x + y - 1;
}

// z = 3x^2 + xy + 2y^2 - x - 4y
// dz/dy = x + 4y - 4
double dz_dy(double x, double y)
{
    return x + 4 * y - 4;
}

typedef struct {
    double x;
    double y;
} Coordinate;

Coordinate gradient_descent(double x, double y)
{
    const int n = 100000;
    for (int i = 0; i < n; i++) {
        const double lambda = 0.1;
        const double eps = 1e-6;

        double xNext = x - lambda * dz_dx(x, y);
        double yNext = y - lambda * dz_dy(x, y);

        if (fabs(xNext - x) < eps && fabs(yNext - y) < eps) {
            x = xNext;
            y = yNext;
            break;
        }

        x = xNext;
        y = yNext;
    }

    Coordinate coordinate = { x, y };
    return coordinate;
}

int main()
{
    double x;
    double y;
    const double eps = 0.0005;

    SCAN_DOUBLE(x);
    SCAN_DOUBLE(y);

    Coordinate coordinate = gradient_descent(x, y);
    x = coordinate.x;
    y = coordinate.y;

    if (x < eps) {
        x = 0;
    }
    if (y < eps) {
        y = 0;
    }

    printf("%.3lf %.3lf\n", x, y);

    return 0;
}