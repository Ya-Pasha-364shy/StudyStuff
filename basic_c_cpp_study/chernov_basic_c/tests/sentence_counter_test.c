#include <stdio.h>
/* needs for cmocka */

#include <setjmp.h>

#include <stddef.h>

#include <stdarg.h>
/* cmocka lib */
#include <cmocka.h>

#include <stdlib.h>
#include <string.h>

#include "sentence_counter.h"

#define UNUSED(x) (void)(x)

const char* sentence_counter_test_invalid = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_invalid.txt";
const char* sentence_counter_test_valid1 = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_valid1.txt";
const char* sentence_counter_test_valid2 = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_valid2.txt";
const char* sentence_counter_test_valid3 = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_valid3.txt";
const char* sentence_counter_test_valid4 = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_valid4.txt";
const char* sentence_counter_test_valid5 = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_valid5.txt";

// при компиляции с -Wl,--wrap=read_lines все вызовы read_lines -> __wrap_read_lines
int __wrap_read_lines(const char* filename, char lines[256][256])
{
    UNUSED(filename);

    // mock_type извлекает значение из очереди, которую задаёт will_return.
    // Таким образом, мы изолируем исполнение функции read_lines внутри longest_sentence_in_file.
    int mocked_result = mock_type(int);
    if (mocked_result == 1) {
        return 1;
    }

    FILE* fp = fopen(filename, "r");
    __ssize_t read = 0;
    size_t length = 0, iterator = 0;
    char* tmp_line = NULL;

    while ((read = getline(&tmp_line, &length, fp)) != -1) {
        if (read && tmp_line[0] != '\n') {
            if (NULL == strncpy(lines[iterator], tmp_line, 255)) {
                perror("");
                return 1;
            }
            if (strlen(tmp_line) >= 256) {
                lines[iterator][255] = '\0';
            } else {
                size_t cur_sz = strlen(lines[iterator]);

                if (lines[iterator][cur_sz - 1] == '\n') {
                    lines[iterator][cur_sz - 1] = '\0';
                }
            }
            iterator++;
        }
    }
    if (iterator < 256) {
        lines[iterator][0] = '\0';
    }

    return mocked_result;
}

/**
 * тестируем ф-ию `longest_sentence_in_file`:
 *     1. несуществующий файл - ф-ия должна вернуть ошибку;
 *     2. файл существуют и все предложения меньше 256 символов (255 + '\0') - ф-ия возвращает 0 и определяет самое длинное предложение;
 *     3. файл существует и одно предложение больше 256 символов (255 + '\0') - ф-ия возвращает 0 и определяет самое длинное предложение;
 *     4. файл существует и все предложения больше 256 символов (255 + '\0') - ф-ия возвращает 0 и не определяет самое длинное предложение;
 *     5. файл существует и все предложения меньше 256 символов (255 + '\0'), но в нём существует такое предложение, которое имеет несколько символов перевода строки после одного и того же слова -
 *         ф-ия возвращает 0 и определяет самое длинное предложение, причём схлопывает все излишние символы перевода строки.
 *     6. файл существует и максимальное предложение длинной в 255 символов обнаруживается.
 */

static void longest_sentence_test_invalid_file(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 1);

    char longest_sequence[256] = { 0 };
    int actualRes = longest_sentence_in_file(sentence_counter_test_invalid, longest_sequence);
    int expectedRes = 1;

    assert_int_equal(actualRes, expectedRes);
}

static void longest_sentence_test_valid_file1(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);

    char longest_sequence[256] = { 0 };
    int actualRes = longest_sentence_in_file(sentence_counter_test_valid1, longest_sequence);

    int expectedRes = 0;
    assert_int_equal(actualRes, expectedRes);

    const char* longest_sequence_expected = " If yes, i will\ntell u about my long path to success.";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

static void longest_sentence_test_valid_file2(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);

    char longest_sequence[256] = { 0 };
    int actualRes = longest_sentence_in_file(sentence_counter_test_valid2, longest_sequence);

    int expectedRes = 0;
    assert_int_equal(actualRes, expectedRes);

    const char* longest_sequence_expected = " If yes, i will\ntell u about my long path to success.";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

static void longest_sentence_test_valid_file3(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);

    char longest_sequence[256] = { 0 };
    int actualRes = longest_sentence_in_file(sentence_counter_test_valid3, longest_sequence);

    int expectedRes = 0;
    assert_int_equal(actualRes, expectedRes);

    const char* longest_sequence_expected = "";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

static void longest_sentence_test_valid_file4(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);

    char longest_sequence[256] = { 0 };
    int actualRes = longest_sentence_in_file(sentence_counter_test_valid4, longest_sequence);

    int expectedRes = 0;
    assert_int_equal(actualRes, expectedRes);

    const char* longest_sequence_expected = " If yes, i will\ntell u about my long path to success.";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

static void longest_sentence_test_valid_file5(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);

    char longest_sequence[256] = { 0 };
    int actualRes = longest_sentence_in_file(sentence_counter_test_valid5, longest_sequence);

    int expectedRes = 0;
    assert_int_equal(actualRes, expectedRes);

    const char* longest_sequence_expected = "aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp qq rr ss tt uu vv ww xx yy zz 1234567890 1234567890 qwerty1234567890 zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz.";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(longest_sentence_test_invalid_file),
        cmocka_unit_test(longest_sentence_test_valid_file1),
        cmocka_unit_test(longest_sentence_test_valid_file2),
        cmocka_unit_test(longest_sentence_test_valid_file3),
        cmocka_unit_test(longest_sentence_test_valid_file4),
        cmocka_unit_test(longest_sentence_test_valid_file5)
    };

    return cmocka_run_group_tests(tests, 0, 0);
}