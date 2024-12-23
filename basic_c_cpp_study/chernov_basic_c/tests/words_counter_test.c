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

/**
 * тестируем функцию `count_words`:
 *     1. было считан набор данных, однако слов в предложении нет - функция должна вернуть 0.
 *     2. в предложении два слова, однако они окружены символами препинания - функция должна вернуть 2.
 *     3. в предложении два слова, однако они содержат цифры, предложение не кончается символом окончания предложения - функция должна вернуть 2.
 *     4. в тексте-рыбе Lorem Ipsum набор предложений, общее число слов в них = 40 - функция должна вернуть 40.
 */

static void words_counter_test1(void** state)
{
    UNUSED(state);

    char sentence[256] = ">...<!!!?`'!   !?!?)() =-=";
    int actualRes = count_words(sentence);
    int expectedRes = 0;

    assert_int_equal(actualRes, expectedRes);
}

static void words_counter_test2(void** state)
{
    UNUSED(state);

    char sentence[256] = "!.. ,Hello, world. ; .<";
    int actualRes = count_words(sentence);
    int expectedRes = 2;

    assert_int_equal(actualRes, expectedRes);
}

static void words_counter_test3(void** state)
{
    UNUSED(state);

    char sentence[256] = "H3ll01337!?>,,,,,wOrlD,,,";
    int actualRes = count_words(sentence);
    int expectedRes = 2;

    assert_int_equal(actualRes, expectedRes);
}

static void words_counter_test4(void** state)
{
    UNUSED(state);

    char sentence[256] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor.";
    int actualRes = count_words(sentence);
    int expectedRes = 40;

    assert_int_equal(actualRes, expectedRes);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(words_counter_test1),
        cmocka_unit_test(words_counter_test2),
        cmocka_unit_test(words_counter_test3),
        cmocka_unit_test(words_counter_test4)
    };

    return cmocka_run_group_tests(tests, 0, 0);
}