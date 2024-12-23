#include <math.h>
#include <stdio.h>

/**
 * Description:
 *
 * Методом Эйлера найти решение задачи Коши для уравнения y'=y/x-ln(x)/x
 * на заданном промежутке.
 * Промежуток задается подающимися числами a и b (типа double).
 * Начальное условие c (y(a)=c) подается на вход как число типа double.
 * Выведите значение решения задачи Коши в конце рассматриваемого промежутка (y(b)).
 *
 * Ограничения:
 *
 * a и b (начало и конец промежутка) - типа double
 * c (начальное условие) - типа double
 * Ответ выводится в формате 0.xxxx
 * (четыре знака после запятой, округляя математически, т.е. вместо 0.11115 выводим 0.1112)
 */

#define SCAN_DOUBLE(var)                                            \
    do {                                                            \
        int ret;                                                    \
        if ((ret = scanf("%lf", &var)) != 1) {                      \
            printf("failed to read " #var " with code: %d\n", ret); \
            return -1;                                              \
        }                                                           \
    } while (0);

double F_1(double x, double y)
{
    return y / x - log(x) / x;
}

double function(double a, double b, double c)
{
    const int n = 20000000;
    double h = (b - a) / n;
    // y'(a)=c
    double x = a;
    double y = c;

    for (int i = 0; i < n; i++) {
        x += h;
        y += h * F_1(x, y);
    }

    return y;
}

int main()
{
    double a;
    double b;
    double c;

    SCAN_DOUBLE(a);
    SCAN_DOUBLE(b);
    SCAN_DOUBLE(c);

    printf("%.4lf\n", function(a, b, c));

    return 0;
}