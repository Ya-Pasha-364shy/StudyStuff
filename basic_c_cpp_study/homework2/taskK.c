#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#define MAX_BUFFER_SZ 100

/**
 * Описание:
 *
 * На вход подается строка s, заканчивающаяся символом "\n".
 * Выведите строку в обратном порядке (без учета символа "\n").
 * Не используйте массивы.
 */

int main()
{
    char input[MAX_BUFFER_SZ + 1] = "";
    if (scanf("%s", input) != 1) {
        return EXIT_FAILURE;
    }

    char tmp;
    size_t input_length = strlen(input);

    for (size_t i = 0; i < input_length / 2; ++i) {
        tmp = input[input_length - 1 - i];
        input[input_length - 1 - i] = input[i];
        input[i] = tmp;
    }

    printf("%s\n", input);
    return EXIT_SUCCESS;
}