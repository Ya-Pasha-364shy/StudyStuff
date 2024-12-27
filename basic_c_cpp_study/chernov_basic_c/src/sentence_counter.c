#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reader.h"
#include "sentence_counter.h"

/**
 * @brief
 * Функция принимает строку, размерность которой ограничена 256 символами.
 * Строка должна заканчиваться на знак пунктуации - это '.','!','?' и прочие.
 * Возвращает число слов в этом предложении. Словом считается любая
 * последовательность, состоящая из букв и цифр.
 */
int count_words(const char sentence[MAX_STR_LENGTH])
{
    size_t words_number = 0;
    bool is_valid_word = false;

    for (size_t i = 0; i < MAX_STR_LENGTH && sentence[i]; i++) {
        if (is_valid_word && (ispunct(sentence[i]) || isspace(sentence[i]))) {
            words_number++;
            is_valid_word = false;
            continue;
        }
        if (!is_valid_word && isalnum(sentence[i])) {
            is_valid_word = true;
        }
    }

    return words_number;
}

static bool is_end_of_sentence(char chr)
{
    if (chr == '.' || chr == '!' || chr == '?' || chr == '\0') {
        return true;
    }
    return false;
}

/**
 * @brief
 * Функция принимает путь до файла и массив, который будет содержать
 * самое длинное предложение в тексте, после исполнения данной ф-ии.
 *
 * Возвращает 1, если что-то пошло не так, попутно логируя ошибку в stdout.
 * Возвращает 0, если текст был успешно проанализирован.
 */
int longest_sentence_in_file(const char* filename, char longest_sentence[MAX_STR_LENGTH])
{
    char lines[MAX_STR_LENGTH][MAX_STR_LENGTH];
    int res = read_lines(filename, lines);
    if (res) {
        return 1;
    }

    size_t iterator = 0;
    bool sentence_keep = false;
    int max_words_number = 0;
    char current_sentence[MAX_STR_LENGTH] = { 0 };

    for (size_t i = 0; i < MAX_STR_LENGTH; i++) {
        if (!lines[i][0]) {
            break;
        }
        for (size_t j = 0; j < MAX_STR_LENGTH; j++) {
            if (!lines[i][j]) {
                if (sentence_keep && iterator < MAX_STR_LENGTH - 1) {
                    current_sentence[iterator++] = '\n';
                }
                break;
            }

            if (iterator == MAX_STR_LENGTH) {
                // не предложение: слишком длинное.
                memset(current_sentence, 0, iterator);
                iterator = 0;
            }

            if (is_end_of_sentence(lines[i][j])) {
                current_sentence[iterator++] = lines[i][j];

                int words_number_per_sentence = count_words(current_sentence);
                if (words_number_per_sentence > max_words_number) {
                    strncpy(longest_sentence, current_sentence, 255);
                    max_words_number = words_number_per_sentence;
                }

                sentence_keep = false;
                memset(current_sentence, 0, iterator);
                iterator = 0;

            } else {
                sentence_keep = true;
                current_sentence[iterator++] = lines[i][j];
            }
        }
    }

    return 0;
}