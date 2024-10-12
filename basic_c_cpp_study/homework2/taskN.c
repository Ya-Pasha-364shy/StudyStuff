#include <stdio.h>

typedef unsigned int ui;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/**
 * Description:
 *
 * На вход подается натуральное число n.
 * Требуется нарисовать пирамиду высоты n.
 * Блоки пирамиды обозначаются "*".
 * Пустое пространство заполняется точками ".".
 */

int main(void)
{
    ui n = 0, j = 0;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    for (ui i = 0; i < n; i++, j = 0) {
        while (j++ < n - i - 1) {
            printf(".");
        }

        j = 0;
        while (j++ < 2 * i + 1) {
            printf("*");
        }

        j = 0;
        while (j++ < n - i - 1) {
            printf(".");
        }

        printf("\n");
    }

    return EXIT_SUCCESS;
}