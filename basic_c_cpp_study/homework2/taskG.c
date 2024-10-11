#include <stdio.h>

#include <ctype.h>

#include <stdlib.h>

#include <stdbool.h>

#define MAX_TEMPLATE_STR_SZ 50

/**
 * Описание:
 *
 * Предложение в данной задаче - это список токенов,
 * разделенных единичными пробелами (без повторяющихся
 * и завершающих пробелов).
 * Каждый токен - это либо положительное число состоящее
 * из цифр 0-9 (без ведущих нулей), или слово, состоящее
 * из малых английских букв.
 * На вход подается строка s (представляющая предложение), завершающаяся символом '\n'.
 * Вы должны проверить, что последовательность всех чисел в строке является строго возрастающей
 * (слева направо, т.е., данное число больше всех чисел, которые расположены левее его).
 * Выведите 1, если это так, 0 - если последовательность не является строго возрастающей.
 */

int main()
{
    bool steel_number = true, rv = true;
    char chr;
    unsigned int index = 0;
    int previous_number = -1;
    char word[MAX_TEMPLATE_STR_SZ + 1] = "";

    while ((chr = getchar()) != EOF) {
        if (isspace(chr) || chr == '\n') {
            if (index > 0) {
                word[index] = '\0';
                if (steel_number) {
                    int tmp = atoi(word);
                    if (tmp > previous_number) {
                        previous_number = tmp;
                    } else {
                        rv = false;
                        break;
                    }
                } else {
                    steel_number = true;
                }
                index = 0;
            }
            if (chr == '\n') {
                break;
            }
        } else {
            if (index < (sizeof(word) - 1)) {
                if (steel_number) {
                    if (!isdigit(chr)) {
                        steel_number = false;
                    }
                }
                word[index++] = chr;
            }
        }
    }

    printf("%d\n", rv);
    return EXIT_SUCCESS;
}