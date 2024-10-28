#include <stdio.h>

#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define DOT '.'
#define SPACE ' '

#define MAX_BUFFER_SIZE 512

/**
 * Description:
 * Дан файл, состоящий из нескольких предложений,
 * состоящих из латинских символов и знаков препинания.
 * Каждое предложение оканчивается точкой.
 * Разделение по строкам может быть, а может и не быть :)
 *
 * Требуется найти самое большое предложение по словам.
 */

int main(void)
{
    FILE* fp = fopen("text.txt", "r");
    if (fp == NULL) {
        perror("");
        return EXIT_FAILURE;
    }

    char chr;
    char line[MAX_BUFFER_SIZE] = "";
    char lines[MAX_BUFFER_SIZE][MAX_BUFFER_SIZE];
    size_t max_words_number = 0, words_number,
           line_length = 0, i = 0, max_i = 0;

    while ((chr = fgetc(fp)) != EOF) {
        line[line_length++] = chr;
        if (chr == DOT) {
            char* line_p = line;
            if (*line_p == SPACE) {
                line_p++;
            }

            words_number = 1;
            for (size_t j = 0; j < line_length; j++) {
                if (line_p[j] == SPACE) {
                    words_number++;
                }
            }
            if (words_number > max_words_number) {
                max_words_number = words_number;
                max_i = i;
            }

            (void)strncpy(lines[i++], line_p, line_length);
            memset(line, 0, line_length);
            line_length = 0;
        }
    }

    printf("%s\n%lu\n", lines[max_i], max_words_number);
    fclose(fp);
    return EXIT_SUCCESS;
}