#include <stdio.h>

#include <stdbool.h>

#include <math.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define ui unsigned int

/**
 * Description:
 *
 * Дан массив длины N чисел с плавающей точкой одинарной точности (float).
 * Массив упорядочен, но циклически сдвинут на k элементов вправо (k неизвестно), например:
 * 1 2 3 4 5 --> сдвиг на k=2 вправо --> 4 5 1 2 3
 *
 * Далее на вход подаётся M чисел.
 * Требуется указать их позицию в этом массиве. Учтите, что числа считаются равными, если их модули отличаются не более, чем на eps
 *
 * Вход:
 * eps
 * N
 * Далее N эл-ов через пробел (x_i)
 * M
 * M-чисел (y_i) типа float каждый на новой строке
 *
 * Ожидается:
 * M ответов, каждый на новой строке. Позиция в массиве, если число найдено. 0, если числа нет.
 */

int findPivot(float arr[], float eps, ui size)
{
    int left = 0, right = size - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        float diff = arr[mid] - arr[right];
        if (fabsf(diff) > eps && diff > 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int binarySearch(float arr[], int left, int right, float target, float eps)
{
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (fabsf(arr[mid] - target) < eps) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int checkInArray(float eps, float needle, float array[], ui N, int pivot)
{
    if (needle >= array[pivot] && needle <= array[N - 1]) {
        // все числа после pivot строго возрастают, но меньше последнего элемента
        return binarySearch(array, pivot, N - 1, needle, eps);
    } else {
        // число, которое нам нужно, может быть слева
        return binarySearch(array, 0, pivot - 1, needle, eps);
    }
    return -1;
}

int main(void)
{
    float eps, search_value;
    ui N, M, i = 0;
    int matched_index = 0, pivot;

    if (scanf("%f", &eps) != 1) {
        return EXIT_FAILURE;
    }

    if (scanf("%u", &N) != 1) {
        return EXIT_FAILURE;
    }

    float array[N];
    while (i < N) {
        if (scanf("%f", &array[i]) != 1) {
            return EXIT_FAILURE;
        }
        ++i;
    }

    pivot = findPivot(array, eps, N);

    if (scanf("%u", &M) != 1) {
        return EXIT_FAILURE;
    }

    i = 0;
    while (i < M) {
        if (scanf("%f", &search_value) != 1) {
            return EXIT_FAILURE;
        }

        matched_index = checkInArray(eps, search_value, array, N, pivot);
        printf("%d\n", matched_index + 1);

        ++i;
    }

    return EXIT_SUCCESS;
}