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
int count_words(const char sentence[256])
{
    size_t words_number = 0;
    bool is_valid_word = false;

    for (size_t i = 0; i < 256 && sentence[i]; i++) {
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

static bool isEndOfSentence(char chr)
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
int longest_sentence_in_file(const char* filename, char longest_sentence[256])
{
    char lines[256][256];
    int res = read_lines(filename, lines);
    if (res) {
        return 1;
    }

    size_t iterator = 0;
    bool sentence_keep = false;
    int max_words_number = 0;
    int words_number_per_sentence = 0;

    char current_sentence[256] = { 0 };

    for (size_t i = 0; i < 256; i++) {
        for (size_t j = 0; j < 256; j++) {
            if (!lines[i][0]) {
                goto exit;
            } else if (!lines[i][j]) {
                if (sentence_keep) {
                    if (iterator < 255) {
                        current_sentence[iterator++] = '\n';
                    }
                }
                break;
            }

            if (iterator == 256) {
                // не предложение: слишком длинное.
                memset(current_sentence, 0, iterator);
                iterator = 0;
            }

            if (isEndOfSentence(lines[i][j])) {
                current_sentence[iterator++] = lines[i][j];

                words_number_per_sentence = count_words(current_sentence);

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

exit:
    return 0;
}