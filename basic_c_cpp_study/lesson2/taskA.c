#include <stdio.h>

#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_BUFF_SZ 255
#define MAX_WORD_SZ 26

#define DELIMETER_STR " "

/**
 * Description:
 *
 * Дан файл lines.txt, содержащий несколько предложений,
 * каждое с новой строки. Выведите самое большое предложение по словам,
 * а также само количество слов
 */

int main(void)
{
    size_t i = 0;
    FILE* fp = fopen("lines.txt", "r");
    if (fp == NULL) {
        perror("");
        return EXIT_FAILURE;
    }

    char* word = NULL;
    size_t max_i = 0, max_words_cnt = 0, word_length = 0;
    char lines[MAX_BUFF_SZ][MAX_BUFF_SZ] = {};

    while (!feof(fp)) {
        char tmp_line[MAX_BUFF_SZ] = "";
        if (!fgets(tmp_line, MAX_BUFF_SZ, fp)) {
            continue;
        }
        word_length = strcspn(tmp_line, "\n");
        tmp_line[word_length] = '\0';
        (void)strncpy(lines[i], tmp_line, word_length);

        size_t word_cnt = 0;
        word = strtok(tmp_line, DELIMETER_STR);

        while (word) {
            word = strtok(NULL, DELIMETER_STR);
            word_cnt++;
        }

        if (word_cnt > max_words_cnt) {
            max_words_cnt = word_cnt;
            max_i = i;
        }
        i++;
    }

    printf("%s\n%lu\n", lines[max_i], max_words_cnt);
    fclose(fp);
    return EXIT_SUCCESS;
}