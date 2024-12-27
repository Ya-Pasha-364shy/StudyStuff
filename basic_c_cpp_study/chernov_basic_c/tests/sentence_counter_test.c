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
const char* sentence_counter_test_valid5 = "tests/longest_sentence_in_file_tests_files/sentence_counter_test_valid5.txt";

int __wrap_read_lines(const char* filename, char lines[MAX_STR_LENGTH][MAX_STR_LENGTH])
{
    UNUSED(filename);

    // mock_type/mock_ptr_type извлекает значение из очереди, которую задаёт will_return.
    // Таким образом, мы изолируем исполнение функции read_lines внутри longest_sentence_in_file.
    int rc = mock_type(int);

    size_t iterator = 0;
    char** test_text = mock_ptr_type(char**);
    if (test_text != NULL) {
        for (; test_text[iterator]; iterator++) {
            strcpy(lines[iterator], test_text[iterator]);
        }
    }

    return rc;
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
    will_return(__wrap_read_lines, NULL);

    char longest_sequence[MAX_STR_LENGTH] = { 0 };
    int actual_rs = longest_sentence_in_file(sentence_counter_test_invalid, longest_sequence);
    int expected_rs = 1;

    assert_int_equal(actual_rs, expected_rs);
}

static void longest_sentence_test_valid_file1(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);
    char* test_text[] =
    {
        "hello world, my name is Pavel Chernov.",
        "Do u want listen about my story ? If yes, i will",
        "tell u about my long path to success.",
        "Just relax and listen.",
        NULL
    };
    will_return(__wrap_read_lines, test_text);

    char longest_sequence[MAX_STR_LENGTH] = { 0 };
    int actual_rs = longest_sentence_in_file(sentence_counter_test_valid1, longest_sequence);

    int expected_rs = 0;
    assert_int_equal(actual_rs, expected_rs);

    const char* longest_sequence_expected = " If yes, i will\ntell u about my long path to success.";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}
static void longest_sentence_test_valid_file2(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);
    char* test_text[MAX_STR_LENGTH] =
    {
        "hello world, my name is Pavel Chernov.",
        "Do u want listen about my story ? If yes, i will",
        "tell u about my long path to success.",
        "Just relax and listen.",
        NULL
    };
    will_return(__wrap_read_lines, test_text);

    char longest_sequence[MAX_STR_LENGTH] = { 0 };
    int actual_rs = longest_sentence_in_file(sentence_counter_test_valid2, longest_sequence);

    int expected_rs = 0;
    assert_int_equal(actual_rs, expected_rs);

    const char* longest_sequence_expected = " If yes, i will\ntell u about my long path to success.";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

static void longest_sentence_test_valid_file3(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);
    char* test_text[MAX_STR_LENGTH] =
    {
        "This is very big sentencee with alphabet sequence: AA BB CC DD EE FF GG HH II JJ KK LL MM NN OO PP QQ RR SS TT UU VV WW XX YY ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        "This is very big sentencee with alphabet sequence: AA BB CC DD EE FF GG HH II JJ KK LL MM NN OO PP QQ RR SS TT UU VV WW XX YY ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        "This is very big sentencee with alphabet sequence: AA BB CC DD EE FF GG HH II JJ KK LL MM NN OO PP QQ RR SS TT UU VV WW XX YY ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        "This is very big sentencee with alphabet sequence: AA BB CC DD EE FF GG HH II JJ KK LL MM NN OO PP QQ RR SS TT UU VV WW XX YY ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        "This is very big sentencee with alphabet sequence: AA BB CC DD EE FF GG HH II JJ KK LL MM NN OO PP QQ RR SS TT UU VV WW XX YY ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        NULL
    };
    will_return(__wrap_read_lines, test_text);

    char longest_sequence[MAX_STR_LENGTH] = { 0 };
    int actual_rs = longest_sentence_in_file(sentence_counter_test_valid3, longest_sequence);

    int expected_rs = 0;
    assert_int_equal(actual_rs, expected_rs);

    const char* longest_sequence_expected = "";
    assert_string_equal(longest_sequence, longest_sequence_expected);
}

static void longest_sentence_test_valid_file5(void** state)
{
    UNUSED(state);

    will_return(__wrap_read_lines, 0);
    char* test_text[MAX_STR_LENGTH] =
    {
        "hello world, my name is Pavel Chernov.",
        "Do u want listen about my story ? If yes, i will",
        "tell u about my long path to success.",
        "Just relax and listen.",
        "aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp qq rr ss tt uu vv ww xx yy zz 1234567890 1234567890 qwerty1234567890 zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz.",
        NULL
    };
    will_return(__wrap_read_lines, test_text);

    char longest_sequence[MAX_STR_LENGTH] = { 0 };
    int actual_rs = longest_sentence_in_file(sentence_counter_test_valid5, longest_sequence);

    int expected_rs = 0;
    assert_int_equal(actual_rs, expected_rs);

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
        cmocka_unit_test(longest_sentence_test_valid_file5)
    };

    return cmocka_run_group_tests(tests, 0, 0);
}