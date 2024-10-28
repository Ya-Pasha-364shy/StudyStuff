#include <stdio.h>
#include <stdlib.h>

/**
 * Description:
 *
 * Реализовать функцию:
 * int* cool_int_arr_dup(const int* arr, unsigned long long size, void* (*malloc_func)(unsigned long long num));
 * Задача функции.
 * Выделить память под <size> элементов типа int.
 * Скопировать элементы из <arr> в выделенную память.
 * Вернуть адрес на первый элемент нового массива.
 * Выделение должно осуществляться через указатель на функцию <malloc_func>, которая пришла аргументом.
 * Синтаксис её вызова такой же как у простого вызова оригинальной malloc: void *ptr = malloc_func(<num>);
 */

int* cool_int_arr_dup(const int* arr, unsigned long long size, void* (*malloc_func)(unsigned long long num))
{
    unsigned long long i = 0;
    int* new_arr = (int*)malloc_func(size * sizeof(int));

    while (size > i) {
        *(new_arr + i) = *(arr + i);
        i++;
    }
    return new_arr;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *new_arr = cool_int_arr_dup(arr, 5, malloc);

    for (int i = 0; i < 5; i++) {
        printf("%d\n", new_arr[i]);
    }

    free(new_arr);

    return EXIT_SUCCESS;
}