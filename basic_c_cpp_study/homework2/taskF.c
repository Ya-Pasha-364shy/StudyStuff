#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

#define ALPHABET_SZ 26
#define MAX_TEMPLATE_STR_SZ 50

/**
 * Описание:
 *
 * На вход подаются две строки.
 * Первая строка (str1) - слово из малых английских букв.
 * Вторая (str2) - несколько слов (также из малых английских букв),
 * разделенных пробелами.
 * Выведите число слов, которые состоят из тех же букв,
 * что и слово из первой строки. Количество букв при этом может различаться
 * (т.е., считается, что слова 'abab' и 'aaaab' состоят из одних и тех же букв).
 */

static size_t template_len;

int check(char* template, char* word)
{
    int template_count[ALPHABET_SZ] = { 0 };
    int word_count[ALPHABET_SZ] = { 0 };

    for (int i = 0; template[i] != 0; i++) {
        template_count[template[i] - 'a']++;
    }

    for (int i = 0; word[i] != 0; i++) {
        word_count[word[i] - 'a']++;
    }

    for (int i = 0; i < ALPHABET_SZ; i++) {
        if ((!template_count[i] && word_count[i] > 0) || (!word_count[i] && template_count[i] > 0)) {
            return 0;
        }
    }

    return 1;
}

int main()
{
    char chr;
    size_t index = 0;
    size_t counter = 0;

    char str1[MAX_TEMPLATE_STR_SZ + 1] = "";
    char word[MAX_TEMPLATE_STR_SZ + 1] = "";
    if (scanf("%[^\n]%*c", str1) != 1) {
        return EXIT_FAILURE;
    }
    template_len = strlen(str1);

    while ((chr = getchar()) != EOF) {
        if (chr == '\n') {
            if (index > 0) {
                word[index] = '\0';
                if (check(str1, word)) {
                    counter++;
                }
                index = 0;
            }
            break;
        } else if (isspace(chr)) {
            if (index > 0) {
                word[index] = '\0';
                if (check(str1, word)) {
                    counter++;
                }
                index = 0;
            }
        } else {
            if (index < (sizeof(word) - 1)) {
                word[index++] = chr;
            }
        }
    }

    printf("%lu\n", counter);
    return EXIT_SUCCESS;
}